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

int handle_load_game(char* args[4], GameState* game_state) {
    if(args[0] == NULL) {
        strcpy(game_state->message, "Loaded from default.dat");
        read_game_state_from_file("default.dat", game_state);
        return 0;
    }
    strcpy(game_state->message, "OK");
    read_game_state_from_file(args[0], game_state);
    return 1;
}

int handle_save_game(char* args[4], GameState* game_state) {
    if(args[0] == NULL) {
        strcpy(game_state->message, "Saved to default.dat");
        write_game_state_to_file("default.dat", game_state);
        return 0;
    }
    strcpy(game_state->message, "OK");
    write_game_state_to_file(args[0], game_state);
    return 1;
}

int handle_load_deck(char* args[4], GameState* game_state) {
    // TODO - Make error handling for this
    if(args[0] == NULL) {
        game_state -> deck = create_deck();
        empty_columns(game_state);
        empty_foundations(game_state);
        show_deck(game_state, 1);
    }
    else {
        game_state -> deck = load_deck_from_file_name(args[0]);
        empty_columns(game_state);
        empty_foundations(game_state);
        show_deck(game_state, 1);
    }
    return 1;
}


int handle_save_deck(char* args[4], GameState* game_state) {
    if(args[0] == NULL) {
        save_deck_to_file(game_state->deck);
    }
    else {
        save_deck_to_file_name(game_state->deck, args[0]);
    }
    return 1;
}

int switch_to_play_phase(char* args[4], GameState* game_state) {
    game_state->phase = PLAY;
    empty_columns(game_state);
    empty_foundations(game_state);
    game_init(game_state);
    return 1;
}

int handle_quit_game(char* args[4], GameState* game_state) {
    game_state->phase = STARTUP;
    empty_columns(game_state);
    empty_foundations(game_state);
    return 1;
}

int handle_quit_application(char* args[4], GameState* game_state) {
    destroy_game_state(game_state);
    return -1; // This is the special signal to quit the application
}

int handle_shuffle_deck(char* args[4], GameState* game_state) {
    game_state->deck = shuffle_deck(game_state->deck);
    return 1;
}

int handle_show_deck(char* args[4], GameState* game_state) {
    empty_columns(game_state);
    empty_foundations(game_state);
    show_deck(game_state,0);
    return 1;
}

int handle_split_deck(char* args[4], GameState* game_state) {
    if (args[1] == NULL) {
        split_deck(game_state->deck);
    }
    else {
        // TODO - Make sure args[1] is a number before converting
        if (!atoi(args[1])) {
            return 0;
        }
        else {
            split_deck_int(game_state->deck, atoi(args[1]));
        }
    }
    return 1;
}