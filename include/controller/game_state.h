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

void destroy_game_state(GameState* game_state);