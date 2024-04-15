#include <view/terminal/command_parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <model/card.h>

char* valid_startup_commands[] = {"LD", "SW", "SI", "SR", "SD", "QQ" };
char* valid_game_commands[] = { "P", "Q", "U", "R", "S", "L" };

int validate_startup_command(const ParsedCommand* cmd) {
    if (cmd == NULL) return 0;

    for (int i = 0; i < 6; i++) {
        if (strcmp(cmd->command, valid_startup_commands[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int validate_game_command(const ParsedCommand* cmd) {
    if (cmd == NULL) return 0;
    for (int i = 0; i < 6; i++) {
        if (strcmp(cmd->command, valid_game_commands[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int validate_command(const ParsedCommand* command, GameState state, char* message) {
    if (command == NULL) {
        strcpy(message, "No command provided");
        return 0;
    }

    if(is_empty(command->command)) {
        strcpy(message, "No command provided");
        return 0;
    }

    int valid_game_command = validate_game_command(command);
    int valid_startup_command = validate_startup_command(command);

    if (!valid_game_command && !valid_startup_command) {
        strcpy(message, "Invalid command");
        return 0;
    }

    if (state == STARTUP && !valid_startup_command) {
        strcpy(message, "Can't use that command in the startup phase");
        return 0;
    }

    if (state == PLAY && !valid_game_command) {
        strcpy(message, "Can't use that command in the play phase");
        return 0;
    }

    strcpy(message, "OK");
    return 1;
}

ParsedCommand* extract_command(const char* command) {
    ParsedCommand* cmd = malloc(sizeof(ParsedCommand));
    if (cmd == NULL) return NULL;

    char *command_copy = strdup(command);

    if (command_copy == NULL) {
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
    trim(cmd->command);
    int arg_count = 0;

    // Initialize all arguments to NULL
    for (int i = 0; i < MAX_ARGS; i++) {
        cmd->args[i] = NULL;
    }

    // Save the arguments
    char *arg;
    while (arg_count < MAX_ARGS && (arg = strtok_r(NULL, " ", &rest)) != NULL) {
        cmd->args[arg_count] = strdup(arg);
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

int evaluate_command(const ParsedCommand* command, char* message) {
    if (command == NULL) return 0;
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
}

CommandType get_command_type(const char* command) {
    if (strstr(command, "->") != NULL) {
        return GAME_MOVE;
    }
    return COMMAND;
}

int parse_command(const char* command, GameState state, char* message, char* last_command) {
    if(state == PLAY) {
        if(get_command_type(command) == GAME_MOVE) {
            if(parse_game_move(command, message, last_command)) {
                strcpy(message, "OK");
                return 1;
            }
            return 0;
        }
    }
    ParsedCommand *cmd = extract_command(command);

    if (!validate_command(cmd, state, message)) {
        return 0;
    }

    evaluate_command(cmd, message);

    char* command_copy = strdup(command);
    trim(command_copy);
    strcpy(last_command, command_copy); // copy the command to the last command message
    free(command_copy);
    destroy_command(cmd);
    return 1;
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
    if(from == NULL || to == NULL) {
        free(from);
        free(to);
        free(game_move_copy);
        free(move);
        return NULL;
    }
    move->to = strdup(to);
    trim(move->to);

    // Parse the left side
    move->from = extract_move_source(from);
    free(from);
    free(game_move_copy);
    return move;
}

GameMoveSource *extract_move_source(const char *source) {
    char *source_copy = strdup(source);
    GameMoveSource *game_move_source = malloc(sizeof(GameMoveSource));
    game_move_source->column = NULL;
    game_move_source->card = NULL;
    game_move_source->pile = NULL;
    if (is_specific_card(source)) {
        char *rest;
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

    if (strstr(command, "C") != NULL) {
        return 1;
    }
    return 0;
}

int is_foundation_pile(const char *command) {
    if (strstr(command, "F") != NULL) {
        return 1;
    }
    return 0;
}

int evaluate_game_move(const GameMove *move, char *message) {
    if (move == NULL) return 0;

    return 1;
}

void trim(char *str) {
    char *start, *end;

    // Trim leading space
    for (start = str; *start; start++) {
        if (!isspace((unsigned char)start[0]))
            break;
    }

    // Trim trailing space
    for (end = start + strlen(start); end > start; end--) {
        if (!isspace((unsigned char)end[-1]))
            break;
    }

    *end = 0;  // Set new null terminator

    // Shift the trimmed string to the start of the buffer
    if (start > str)
        memmove(str, start, end - start + 1);
}

void remove_all_spaces(char *str) {
    trim(str);
    char *i = str;
    char *j = str;
    while(*j != 0) {
        *i = *j++;
        if(*i != ' ') i++;
    }
    *i = 0;
}

int is_empty(char *str) {
    if (str == NULL) return 1;
    if (strlen(str) == 0) return 1;
    return 0;
}

int validate_game_move_syntax(const GameMove *move, char *message) {
    if (move == NULL) {
        strcpy(message, "No move provided");
        return 0;
    }

    if (!validate_foundation_pile(move->to) && !validate_column(move->to)) {
        strcpy(message, "Invalid destination location");
        return 0;
    }

    if (move->from == NULL) {
        strcpy(message, "Invalid source location");
        return 0;
    }

    if (move->from->pile != NULL) {
        if (move->from->card != NULL) {
            strcpy(message, "Cards can only be moved from the top of the foundation piles");
            return 0;
        }
        if (!validate_foundation_pile(move->from->pile)) {
            strcpy(message, "Invalid foundation pile");
            return 0;
        }
    }

    if (move->from->card != NULL) {
        if (!validate_card_input(move->from->card)) {
            strcpy(message, "Invalid card");
            return 0;
        }
    }

    if (move->from->column != NULL) {
        if (!validate_column(move->from->column)) {
            strcpy(message, "Invalid column");
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

int parse_game_move(const char* command, char* message, char* last_command) {
    char* command_copy = strdup(command);
    remove_all_spaces(command_copy);
    GameMove *move = extract_game_move(command_copy);
    if(!validate_game_move_syntax(move, message)) {
        destroy_game_move(move);
        return 0;
    }
    evaluate_game_move(move, message);
    strcpy(last_command, command_copy);

    free(command_copy);
    destroy_game_move(move);
    return 1;
}