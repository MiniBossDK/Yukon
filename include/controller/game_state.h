#pragma once
#include <model/deck.h>
#include <controller/phase.h>


typedef struct GameState GameState;

struct GameState {
    LinkedCard *deck;
    LinkedCard *column[7];
    LinkedCard *foundation[4];
    Phase phase;
    int game_over;
    char message[100];
    char lastCommand[30];
};

/**
 * Create a new game state with the given deck, columns, and foundation piles.
 */
GameState* create_game_state(LinkedCard* deck, LinkedCard* columns[7], LinkedCard* foundation[4]);

/**
 * Check if the game is over.
 */
int check_win(GameState* game_state);

/**
 * Save the game state to a file.
 */
void write_game_state_to_file(const char* filename, struct GameState* game_state);

/**
 * Load the game state from a file.
 */
void read_game_state_from_file(const char* filename, struct GameState* game_state);

/**
 * Destroy the game state and free the memory.
 */
void destroy_game_state(GameState* game_state);

/**
 * Show the deck of cards.
 */
void show_deck(GameState* game_state, int hidden);

/**
 * Initialize the game.
 */
void game_init(GameState* game_state);