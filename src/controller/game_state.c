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
    FILE *file = fopen(filename, "rb"); // Open the file in binary read mode

    if (file != NULL) {
        // Read the struct from the file
        fread(game_state, sizeof(GameState), 1, file);

        // Close the file
        fclose(file);
    } else {
        printf("Error: Unable to open file for reading.\n");
    }
}

void destroy_game_state(GameState* game_state) {
    free(game_state);
}

void show_deck(GameState* game_state) {
    LinkedCard* deck_clone = clone_deck(game_state->deck);
    int index = 0;
    LinkedCard* temp = deck_clone->next;
    for (int i = 0; i < 52; i++) {
        if (game_state->column[index] != NULL) {
            LinkedCard* temp2 = game_state->column[index];
            temp2 = get_last_card(temp2);
            temp2 -> next = deck_clone;
            deck_clone -> prev = temp2;
            deck_clone->next = NULL;
        } else {
            game_state->column[index] = deck_clone;
            game_state->column[index] -> prev = NULL;
            game_state->column[index] -> next = NULL;
        }
        temp -> prev = NULL;
        if (temp -> next != NULL) {
            temp -> prev = NULL;
            deck_clone = temp;
            temp = deck_clone -> next;
        }
        else {
            deck_clone = temp;
        }

        index++;
        if (index == 7) {
            index = 0;
        }
    }
    deck_clone = NULL;
    destroy_deck(deck_clone);
}

void game_init(GameState* game_state) { // Function to initialize the game

    LinkedCard* deck_clone = clone_deck(game_state->deck); // Clone the deck of cards
    // Initialize the game state
    int index = 0;
    int start_index = 0;
    int end_index = 6;
    int hide_index = 0;

    LinkedCard* temp = deck_clone->next; // Temporary pointer to the deck of cards
    for (int i = 0; i < 52; i++) { // Loop through the deck of cards
        if (game_state->column[index] != NULL) { // If the column is not empty
            LinkedCard* temp2 = game_state->column[index]; // Temporary pointer to the column
            temp2 = get_last_card(temp2); // Get the last card in the column
            temp2 -> next = deck_clone; // Set the next card in the column to the cloned deck
            deck_clone -> prev = temp2; // Set the previous card in the cloned deck to the last card in the column
            deck_clone->next = NULL; // Set the next card in the cloned deck to NULL
            if (index > hide_index) { // If the index is greater than the hide index
                hide_card(deck_clone); // Hide the card
            }
        } else {
            game_state->column[index] = deck_clone; // Set the column to the cloned deck
            if(index > 0) { // If the index is greater than 0
                hide_card(game_state->column[index]); // Hide the card
            }
            game_state->column[index] -> prev = NULL; // Set the previous card in the column to NULL
            game_state->column[index] -> next = NULL; // Set the next card in the column to NULL
        }
        temp -> prev = NULL; // Set the previous card in the deck to NULL
        if (temp -> next != NULL) { // If the next card in the deck is not NULL
            temp -> prev = NULL; // Set the previous card in the deck to NULL
            deck_clone = temp; // Set the cloned deck to the next card in the deck
            temp = deck_clone -> next; // Set the temporary pointer to the next card in the deck
        }
        else {
            deck_clone = temp;// Set the cloned deck to the next card in the deck
        }

        index++; // Increment the index
        // If the index is equal to 6, 36, 41, 45, 48, or 50
        if (i == 6 || i == 36 || i == 41 || i == 45 || i == 48 || i == 50 ) {
            start_index++; // Increment the start index
        }
        if (index > end_index) { // If the index is greater than the end index
            index = start_index; // Set the index to the start index
            hide_index++; // Increment the hide index
        }

    }
    deck_clone = NULL; // Set the cloned deck to NULL
    destroy_deck(deck_clone); // Destroy the cloned deck
}