#include <stdlib.h>
#include "core/foundation_pile.h"

Foundation_Pile* create_foundation_pile(char pile_pos) {
    Foundation_Pile* pile = (Foundation_Pile*)malloc(sizeof(Foundation_Pile));
    pile->pile_pos = pile_pos;
    pile->prev = NULL;
    pile->next = NULL;
    return pile;
}

void destroy_foundation_pile(Foundation_Pile* pile) {
    free(pile);
}

char* get_foundation_pile(Foundation_Pile* pile) {
    char* str = (char*)malloc(3);
    str[0] = 'F';
    str[1] = pile->pile_pos;
    str[2] = '\0';
    return str;
}

LinkedCard* get_last_foundation_card(Foundation_Pile* pile) {
    LinkedCard* card = pile->next;
    while (card->next != NULL) {
        card = card->next;
    }
    return card;
}