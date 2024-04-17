#include <controller/game_state.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


GameState* create_game_state(LinkedCard* deck, LinkedCard* columns[7], LinkedCard* foundation[4]) {
    GameState* game_state = (GameState*)malloc(sizeof(GameState));
    game_state->deck = deck;
    game_state->game_over = 0;
    for(int i = 0; i < 7; i++) {
        game_state->column[i] = columns[i];
    }

    for(int i = 0; i < 4; i++) {
        game_state->foundation[i] = foundation[i];
    }
    game_state->phase = 0;
    strcpy(game_state->message, "Hell");
    strcpy(game_state->lastCommand, "Hell");
    return game_state;
}

int check_win(GameState* game_state) {
    for (int i = 0; i < 4; i++) {
        if (game_state -> foundation[i] == NULL) {
            return 0;
        }
        if (game_state -> foundation[i]-> rank != 'K') {
            return 0;
        }
    }
    return 1;
}

// Function to write a struct to a file
void write_game_state_to_file(const char* filename, GameState* game_state) {
    FILE* file = fopen(filename, "wb"); // Open the file in binary write mode

    if (file != NULL) {
        // Write the struct to the file
        fwrite(game_state, sizeof(GameState), 1, file);

        // Close the file
        fclose(file);
    } else {
        printf("Error: Unable to open file for writing.\n");
    }
}

// Function to read a struct from a file
void read_game_state_from_file(const char* filename, GameState* game_state) {
    FILE* file = fopen(filename, "rb"); // Open the file in binary read mode

    if (file != NULL) {
        // Read the struct from the file
        fread(game_state, sizeof(GameState), 1, file);

        // Close the file
        fclose(file);
    } else {
        printf("Error: Unable to open file for reading.\n");
    }
}