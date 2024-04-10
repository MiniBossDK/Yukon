#include <core/column.h>
#include <stdlib.h>

char* get_column_name(Column* column) {
    char column_name[2];
    column_name[0] = 'C';
    column_name[1] = column->pos;
    return (char*) malloc(sizeof(column_name));
}

Column* create_column(char pos) {
    Column* column = (Column*) malloc(sizeof(Column));
    column->pos = pos;
    column->next = NULL;
    column->prev = NULL;
    return column;
}

void destroy_column(Column* column) {
    while(column->next != NULL) {
        LinkedCard* temp = (LinkedCard *) column;
        column = (Column *) column->next;
        free(temp);
    }
    free(column);
}

LinkedCard* get_last_column_card(Column* column) {
    LinkedCard* temp = column->next;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}