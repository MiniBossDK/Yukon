#include <model/foundation_pile.h>
#include <model/card.h>
#include <stdlib.h>
#include "controller/game_state.h"

int validate_move_to_foundation(LinkedCard* foundation_card, LinkedCard* moved_card) {
    if(foundation_card == 0) {
        return moved_card->value == 1;
    }
    return (foundation_card->value + 1 == moved_card->value && foundation_card->suit == moved_card->suit);
}

void empty_foundations(GameState* game_state) {
    for (int i = 0; i < 4; i++) {
        LinkedCard* current = game_state->foundation[i];
        while (current != NULL) {
            LinkedCard* next = current->next;
            free(current);
            current = next;
        }
        game_state->foundation[i] = NULL;
    }
}