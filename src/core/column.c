#include <core/column.h>
#include <core/card.h>

int validate_move_to_column(LinkedCard* column_card, LinkedCard* moved_card) {
    if(column_card == 0) {
        return moved_card->value == 13;
    }
    return (column_card->value - 1 == moved_card->value && column_card->suit != moved_card->suit);
}