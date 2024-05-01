#include <controller/handle_commands.h>
#include <model/deck.h>
#include <model/card.h>
#include <model/column.h>
#include <model/foundation_pile.h>
#include <controller/game_state.h>
#include <controller/phase.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int handle_load_game(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 1)) {
        return 0;
    }
    if(args[0] == NULL) {
        strcpy(game_state->message, "Error: No filename provided");
        return 0;
    }
    struct stat buffer;
    args[0][strcspn(args[0], "\r\n")] = 0; //trim newline from filename
    if(stat(args[0], &buffer) == 0) {
        sprintf(game_state->message, "Loaded from %s", args[0]);
        read_game_state_from_file(args[0], game_state);
    } else {
        strcpy(game_state->message, "Error: File not found");
        return 0;
    }
    return 1;
}

int handle_save_game(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 1)) {
        return 0;
    }
    if(args[0] == NULL) {
        strcpy(game_state->message, "Error: No filename provided");
        return 0;
    }
    sprintf(game_state->message, "Saved to %s", args[0]);
    write_game_state_to_file(args[0], game_state);
    return 1;
}

int handle_load_deck(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 1)) {
        return 0;
    }
    if(args[0] == NULL) {
        game_state -> deck = create_deck();
        empty_columns(game_state);
        empty_foundations(game_state);
        show_deck(game_state, 1);
    }
    else {
        printf("Loading deck from file %s\n", args[0]);
        struct stat buffer;
        args[0][strcspn(args[0], "\r\n")] = 0; //trim newline from filename
        if(stat(args[0], &buffer) == 0) { // Check if file exists
            LinkedCard* loaded_deck = load_deck_from_file_name(args[0]);
            if(validate_deck(game_state, loaded_deck)) {
                empty_columns(game_state);
                empty_foundations(game_state);
                game_state->deck = loaded_deck;
                show_deck(game_state, 1);
            }
            else {
                return 0;
            }
        }
        else {
            strcpy(game_state->message, "Error: File not found");
            return 0;
        }
    }
    return 1;
}


int handle_save_deck(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 1)) {
        return 0;
    }
    if(!validate_deck_loaded(game_state)){
        return 0;
    }
    if(args[0] == NULL) {
        save_deck_to_file(game_state->deck);
    }
    else {
        args[0][strcspn(args[0], "\r\n")] = 0; //trim newline from filename
        save_deck_to_file_name(game_state->deck, args[0]);
    }
    return 1;
}

int switch_to_play_phase(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 0)) {
        return 0;
    }
    if(!validate_deck_loaded(game_state)) {
        return 0;
    }
    game_state->phase = PLAY;
    empty_columns(game_state);
    empty_foundations(game_state);
    game_init(game_state);
    return 1;
}

int handle_quit_game(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 0)) {
        return 0;
    }
    game_state->phase = STARTUP;
    empty_columns(game_state);
    empty_foundations(game_state);
    return 1;
}

int handle_quit_application(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 0)) {
        return 0;
    }
    destroy_game_state(game_state);
    return -1; // This is the special signal to quit the application
}

int handle_shuffle_deck(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 0)) {
        return 0;
    }
    if(!validate_deck_loaded(game_state)) {
        return 0;
    }
    game_state->deck = shuffle_deck(game_state->deck);
    return 1;
}

int handle_show_deck(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 0)) {
        return 0;
    }
    if(!validate_deck_loaded(game_state)) {
        return 0;
    }
    empty_columns(game_state);
    empty_foundations(game_state);
    show_deck(game_state,0);
    return 1;
}

int handle_split_deck(char* args[4], GameState* game_state) {
    if(!validate_max_args(args, game_state, 2)) {
        return 0;
    }
    if(!validate_deck_loaded(game_state)) {
        return 0;
    }
    if (args[0] == NULL) {
        game_state->deck = split_deck(game_state->deck);
    }
    else {
        if (!atoi(args[0])) {
            strcpy(game_state->message, "Error: Invalid argument! <Integer> must be greater than 0 and less than 52");
            return 0;
        }
        else {
            if (atoi(args[0]) < 1 || atoi(args[0]) > 52) {
                strcpy(game_state->message, "Error: Invalid argument! <Integer> must be greater than 0 and less than 52");
                return 0;
            } else {
                game_state->deck = split_deck_int(game_state->deck, atoi(args[0]));
            }
        }
    }
    return 1;
}

int validate_deck_loaded(GameState* state) {
    if(state->deck == NULL) {
        strcpy(state->message, "Error: No deck loaded");
        return 0;
    }
    return 1;
}

int validate_max_args(char* args[4], GameState* state, int max_args) {
    if(args[max_args] != NULL) {
        strcpy(state->message, "Error: Too many arguments");
        return 0;
    }
    return 1;
}