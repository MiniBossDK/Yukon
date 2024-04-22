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

LinkedCard* get_first_card(const char* card, LinkedCard* foundation) {
    LinkedCard* current = foundation;
    while(current != NULL) {
        if(current->value == card[0] && current->suit == card[1]) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int is_empty_foundation(LinkedCard *foundation_pile) {
    return foundation_pile == NULL;
}