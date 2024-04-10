#pragma once

#include "card.h"

typedef struct Foundation_Pile Foundation_Pile;

struct Foundation_Pile {
    char pile_pos;
    LinkedCard* prev;
    LinkedCard* next;
};
/*
 * Create a foundation pile.
 */
Foundation_Pile* create_foundation_pile(char pile_pos);
/*
 * Destroy the foundation pile.
 */

void destroy_foundation_pile(Foundation_Pile* pile);
/*
 * Get foundation pile name/id.
 */

char* get_foundation_pile(Foundation_Pile* pile);

/*
 * Get the last card in the foundation pile.
 */
LinkedCard* get_last_foundation_card(Foundation_Pile* pile);