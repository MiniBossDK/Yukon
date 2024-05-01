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

GameState* create_game_state(LinkedCard* deck, LinkedCard* columns[7], LinkedCard* foundation[4]);

int check_win(GameState* game_state);

void write_game_state_to_file(const char* filename, struct GameState* game_state);

void read_game_state_from_file(const char* filename, struct GameState* game_state);

void destroy_game_state(GameState* game_state);

void show_deck(GameState* game_state, int hidden);

void game_init(GameState* game_state);

