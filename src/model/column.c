#include <model/column.h>
#include <model/card.h>
#include <controller/game_state.h>
#include <stdlib.h>

int validate_move_to_column(LinkedCard **column_card, LinkedCard* moved_card) {
    if(*column_card == NULL) {
        return moved_card->value == 13;
    }
    return ((*column_card)->value - 1 == moved_card->value && (*column_card)->suit != moved_card->suit);
}

void empty_columns(GameState* game_state) {
    for (int i = 0; i < 7; i++) {
        LinkedCard* current = game_state->column[i];
        while (current != NULL) {
            LinkedCard* next = current->next;
            free(current);
            current = next;
        }
        game_state->column[i] = NULL;
    }
}

LinkedCard* find_card_column(const char* card, LinkedCard* column){
    LinkedCard* current = column;
    while(current != NULL){
        if((current->rank == card[0] && current->suit == card[1]) && !current->hidden){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int is_empty_pile(LinkedCard *pile) {
    return pile == NULL;
}