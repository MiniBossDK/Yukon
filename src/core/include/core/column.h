#pragma once
#include <core/card.h>

typedef struct Column Column;

struct Column {
    char pos;
    LinkedCard* next;
};

char* print_column_name(Column* column);

void create_column(char pos);

void destroy_column(Column* column);