#include <model/foundation_pile.h>
#include <model/card.h>

int validate_move_to_foundation(LinkedCard* foundation_card, LinkedCard* moved_card) {
    if(foundation_card == 0) {
        return moved_card->value == 1;
    }
    return (foundation_card->value + 1 == moved_card->value && foundation_card->suit == moved_card->suit);
}