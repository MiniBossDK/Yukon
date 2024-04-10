#pragma once

#include "card.h"

typedef struct Foundation_Pile Foundation_Pile;

struct Foundation_Pile {
    char pile_pos;
    LinkedCard* next;
};

void create_foundation_pile(char pile_pos);

void destroy_foundation_pile(Foundation_Pile* pile);

char* get_foundation_pile_name(Foundation_Pile* pile);