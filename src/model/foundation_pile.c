#include <model/foundation_pile.h>
#include <stdlib.h>

int validate_move_to_foundation(LinkedCard **foundation_pile, LinkedCard* moved_card) {
    if(moved_card->next != NULL) {
        return 0;
    }
    if(*foundation_pile == NULL) {
        return moved_card->value == 1;
    }
    LinkedCard *top_card = get_top_card(*foundation_pile);
    return top_card->value + 1 == moved_card->value && top_card->suit == moved_card->suit;
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

LinkedCard *get_top_card(LinkedCard *foundation_pile) {
    if(foundation_pile == NULL) {
        return NULL;
    }
    LinkedCard *current = foundation_pile;
    while(current->next != NULL) {
        current = current->next;
    }
    return current;
}