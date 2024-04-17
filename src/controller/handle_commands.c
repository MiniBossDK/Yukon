#include <controller/handle_commands.h>
#include <stdio.h>
#include <string.h>

int handle_load_game(char* args[4], char* message, GameState* game_state) {
    if(args[0] == NULL) {
        strcpy(message, "No file name provided");
        return 0;
    }
    return 1;
}

int handle_save_deck(char* args[4], char* message, GameState* game_state) {
    if(args[0] == NULL) {
        save_deck_to_file(game_state->deck);
    }
    else {
        save_deck_to_file_name(game_state->deck, args[0]);
    }
    return 1;
}

int switch_to_play_phase(char* args[4], char* message, GameState* game_state) {
    return -2; // This is the special signal to switch to the play phase
}

int handle_quit_game(char* args[4], char* message, GameState* game_state) {
    return -3; // This is the special signal to quit the game
}

int handle_quit_application(char* args[4], char* message, GameState* game_state) {
    return -1; // This is the special signal to quit the application
}

int handle_move_card(char* args[4], char* message, GameState* game_state) {
    if(args[0] == NULL) {
        strcpy(message, "No source pile provided");
        return 0;
    }
    if(args[1] == NULL) {
        strcpy(message, "No destination pile provided");
        return 0;
    }
    return 1;
}