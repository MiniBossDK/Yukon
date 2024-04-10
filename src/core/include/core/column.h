#pragma once
#include <core/card.h>

typedef struct Column Column;

struct Column {
    char pos;
    LinkedCard* next;
};

/*
 * Get the textual name of the column.
 */
char* get_column_name(Column* column);

/*
 * Create a column with the given position.
 */
Column* create_column(char pos);

/*
 * Destroys the given column and all the cards that it links to.
 */
void destroy_column(Column* column);