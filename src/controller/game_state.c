#include <controller/game_state.h>
#include <malloc.h>

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
    game_state->messsage = (char*)malloc(100);
    game_state->lastCommand = (char*)malloc(100);
    return game_state;
}