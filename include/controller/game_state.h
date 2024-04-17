#pragma once
#include <model/deck.h>

typedef struct GameState GameState;

struct GameState {
    LinkedCard *deck;
    LinkedCard *column[7];
    LinkedCard *foundation[4];
    int game_over;
    char* messsage;
    char* lastCommand;
};