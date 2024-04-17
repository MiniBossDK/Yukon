#include <controller/handle_commands.h>
#include <model/deck.h>
#include <stdio.h>
#include <string.h>

int handle_load_game(char* args[4], char* message) {
    if(args[0] == NULL) {
        strcpy(message, "No file name provided");
        return 0;
    }
    return 1;
}

int handle_save_deck(char* args[4], char* message) {

    return 1;
}

int switch_to_play_phase(char* args[4], char* message) {

    return -2; // This is the special signal to switch to the play phase
}

int handle_quit_game(char* args[4], char* message) {
    return -3; // This is the special signal to quit the game
}

int handle_quit_application(char* args[4], char* message) {
    return -1; // This is the special signal to quit the application
}