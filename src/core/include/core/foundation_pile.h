#pragma once

#include "card.h"

typedef struct Foundation_Pile Foundation_Pile;

struct Foundation_Pile {
    char pile_pos;
    LinkedCard* next;
};
/*
 * Create a foundation pile.
 */
void create_foundation_pile(char pile_pos);
/*
 * Destroy the foundation pile.
 */

void destroy_foundation_pile(Foundation_Pile* pile);
/*
 * Get foundation pile name/id.
 */

char* get_foundation_pile(Foundation_Pile* pile);