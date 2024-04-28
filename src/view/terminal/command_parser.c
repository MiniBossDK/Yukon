#include <view/terminal/command_parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <controller/handle_commands.h>
#include <controller/handle_game_moves.h>
#include <controller/string_utils.h>

Command commands[] = {
        {"L", handle_load_game},
        {"S", handle_save_game},
        {"LD", handle_load_deck},
        {"SD", handle_save_deck},
        {"QQ", handle_quit_application},
        {"Q", handle_quit_game},
        {"P", switch_to_play_phase},
        {"SW", handle_show_deck},
        {"SR", handle_shuffle_deck},
       {"SI", handle_split_deck},
};

char* valid_startup_commands[] = {"LD", "SW", "SI", "SR", "SD", "QQ", "P" };
char* valid_game_commands[] = { "Q", "U", "R", "S", "L" };

int validate_startup_command(const ParsedCommand* cmd) {
    if (cmd == NULL) return 0;

    for (int i = 0; i < 7; i++) {
        if (strcmp(cmd->command, valid_startup_commands[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int validate_game_command(const ParsedCommand* cmd) {
    if (cmd == NULL) return 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(cmd->command, valid_game_commands[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int validate_command(const ParsedCommand* command, GameState *state) {
    if (command == NULL) {
        strcpy(state->message, "No command provided");
        return 0;
    }

    if(is_empty(command->command)) {
        strcpy(state->message, "No command provided");
        return 0;
    }

    int valid_game_command = validate_game_command(command);
    int valid_startup_command = validate_startup_command(command);

    if (!valid_game_command && !valid_startup_command) {
        strcpy(state->message, "Invalid command");
        return 0;
    }

    if (state->phase == STARTUP && !valid_startup_command) {
        strcpy(state->message, "Command not available in the STARTUP phase");
        return 0;
    }

    if (state->phase == PLAY && !valid_game_command) {
        strcpy(state->message, "Command not available in the PLAY phase");
        return 0;
    }

    strcpy(state->message, "OK");
    return 1;
}

ParsedCommand* extract_command(const char* command) {
    ParsedCommand* cmd = malloc(sizeof(ParsedCommand));
    if (cmd == NULL) return NULL; // Memory allocation failed

    // Duplicate the command to avoid modifying the original string
    char *command_copy = strdup(command);
    if (command_copy == NULL) { // If memory allocation fails, free the allocated memory and return NULL
        free(cmd);
        return NULL;
    }

    char *rest;
    // Save the command (the first token)
    char* parsed_cmd = strtok_r(command_copy, " ", &rest);
    if (parsed_cmd == NULL) {
        free(command_copy);
        free(cmd);
        return NULL;
    }
    cmd->command = strdup(parsed_cmd);
    trim(cmd->command); // Remove leading and trailing spaces
    int arg_count = 0;

    // Initialize all arguments to NULL
    for (int i = 0; i < MAX_ARGS; i++) {
        cmd->args[i] = NULL;
    }

    // Save the arguments
    char *arg;
    while (arg_count < MAX_ARGS && (arg = strtok_r(NULL, " ", &rest)) != NULL) {
        cmd->args[arg_count] = strdup(arg);
        // If memory allocation fails, free all allocated memory and return NULL
        if (cmd->args[arg_count] == NULL) {
            free(command_copy);
            for (int j = 0; j < arg_count; j++) free(cmd->args[j]);
            free(cmd);
            return NULL;
        }
        arg_count++;
    }

    free(command_copy);

    return cmd;
}

int evaluate_command(ParsedCommand* command, GameState *state) {
    if (command == NULL) return 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(command->command, commands[i].name) == 0) {
            return commands[i].func(command->args, state);
        }
    }
    return 1;
}

void destroy_command(ParsedCommand* command) {
    if (command == NULL) return;
    free(command->command);
    for (int i = 0; i < MAX_ARGS; i++) {
        if (command->args[i] != NULL) {
            free(command->args[i]);
        }
    }
    free(command);
}

void destroy_game_move(GameMove* move) {
    if (move == NULL) return;
    if (move->from != NULL) {
        if (move->from->column != NULL) {
            free(move->from->column);
        }
        if (move->from->card != NULL) {
            free(move->from->card);
        }
        if (move->from->pile != NULL) {
            free(move->from->pile);
        }
        free(move->from);
    }
    if (move->to != NULL) {
        free(move->to);
    }
    free(move);
}

CommandType get_command_type(const char* command) {
    // Check if string contains the -> character, if so it is a game move
    // Very basic check, but should be sufficient for now
    if (strstr(command, "->") != NULL) {
        return GAME_MOVE;
    }
    return COMMAND;
}

int parse_command(const char* command, GameState* state) {
    if(state->phase == PLAY) {
        if(get_command_type(command) == GAME_MOVE) {
            // Parse the game move separately from a normal command
            if(parse_game_move(command, state)) {
                strcpy(state->message, "OK");
                return 1;
            }
            return 0;
        }
    }
    ParsedCommand *cmd = extract_command(command);
    to_upper(cmd->command);
    if (!validate_command(cmd, state)) {
        return 0;
    }

    int status = evaluate_command(cmd, state);

    destroy_command(cmd);
    return status;
}

GameMove *extract_game_move(const char* game_move) {
    char *game_move_copy = strdup(game_move);
    if (game_move_copy == NULL) {
        free(game_move_copy);
        return NULL;
    }
    GameMove *move = malloc(sizeof(GameMove));
    if (move == NULL) {
        free(game_move_copy);
        return NULL;
    }
    // Separate the left and right side of the arrow
    char *rest;
    char* from = strdup(strtok_r(game_move_copy, "->", &rest));
    char* to = strdup(strtok_r(NULL, "->", &rest));
    if(from == NULL || to == NULL) { // Memory allocation failed
        free(from);
        free(to);
        free(game_move_copy);
        free(move);
        return NULL;
    }
    move->to = to;
    // Since last part of the last part can contain spaces, we need to trim it
    trim(move->to);

    // Since the from part can be a column, a foundation pile
    // or a specific card, we need to determine the type
    move->from = extract_move_source(from);
    free(from);
    free(game_move_copy);
    return move;
}

GameMoveSource *extract_move_source(const char *source) {
    // Duplicate the source to avoid modifying the original string
    char *source_copy = strdup(source);
    if (source_copy == NULL) {
        free(source_copy);
        return NULL;
    }

    GameMoveSource *game_move_source = malloc(sizeof(GameMoveSource));
    game_move_source->column = NULL;
    game_move_source->card = NULL;
    game_move_source->pile = NULL;
    // If the source contains a : character, it is a specific card
    if (is_specific_card(source)) {
        char *rest;
        // Separate the column and card part of the source
        game_move_source->column = strdup(strtok_r(source_copy, ":", &rest));
        game_move_source->card = strdup(strtok_r(NULL, ":", &rest));
        return game_move_source;
    } else if(is_foundation_pile(source)) {
        game_move_source->pile = strdup(source);
        return game_move_source;
    } else if (is_column(source)) {
        game_move_source->column = strdup(source);
        return game_move_source;
    }
    free(source_copy);
    return NULL;
}

int is_specific_card(const char *command) {
    if (strstr(command, ":") != NULL) {
        return 1;
    }
    return 0;
}

int is_column(const char *command) {
    if(is_specific_card(command)) return 0;

    if (strstr(command, "C") != NULL || strstr(command, "c") != NULL) {
        return 1;
    }
    return 0;
}

int is_foundation_pile(const char *command) {
    if (strstr(command, "F") != NULL || strstr(command, "f") != NULL) {
        return 1;
    }
    return 0;
}

int evaluate_game_move(GameMove *move, GameState *state) {
    if (move == NULL) return 0;
    return handle_game_move(move, state);
}

int validate_game_move_syntax(const GameMove *move, GameState *state) {
    if (move == NULL) {
        strcpy(state->message, "No move provided");
        return 0;
    }

    if (!validate_foundation_pile(move->to) && !validate_column(move->to)) {
        strcpy(state->message, "Invalid destination location");
        return 0;
    }

    if (move->from == NULL) {
        strcpy(state->message, "Invalid source location");
        return 0;
    }

    if (move->from->pile != NULL) {
        if (move->from->card != NULL) {
            // If the user wrote something like: F1:AS, it is invalid
            strcpy(state->message, "Cards can only be moved from the top of the foundation piles");
            return 0;
        }
        if (!validate_foundation_pile(move->from->pile)) {
            strcpy(state->message, "Invalid foundation pile");
            return 0;
        }
    }

    if (move->from->card != NULL) {
        if (!validate_card_input(move->from->card)) {
            strcpy(state->message, "Invalid card");
            return 0;
        }
    }

    if (move->from->column != NULL) {
        if (!validate_column(move->from->column)) {
            strcpy(state->message, "Invalid column");
            return 0;
        }
    }

    return 1;
}

int validate_foundation_pile(const char *pile) {
    if (pile == NULL) return 0;
    if (strlen(pile) != 2) return 0;
    if (pile[0] != 'F') return 0;
    if (pile[1] < '1' || pile[1] > '4') return 0;
    return 1;
}

int validate_column(const char *column) {
    if (column == NULL) return 0;
    if (strlen(column) != 2) return 0;
    if (column[0] != 'C') return 0;
    if (column[1] < '1' || column[1] > '7') return 0;
    return 1;
}

int validate_card_input(const char *card) {
    if (card == NULL) return 0;
    if (strlen(card) != 2) return 0;
    if (!validate_card(card[0], card[1])) return 0;
    return 1;
}

int parse_game_move(const char* command, GameState* state) {
    char* command_copy = strdup(command);
    remove_all_spaces(command_copy);
    to_upper(command_copy);
    GameMove *move = extract_game_move(command_copy);

    if(!validate_game_move_syntax(move, state)) {
        destroy_game_move(move);
        return 0;
    }
    int status = evaluate_game_move(move, state);
    strcpy(state->lastCommand, command_copy);

    free(command_copy);
    destroy_game_move(move);
    return status;
}