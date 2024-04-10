#include <stdio.h>
#include <core/card.h>
#include <core/deck.h>

int main() {
    LinkedCard* deck = create_deck();
    LinkedCard* deck_copy = deck;

    LinkedCard* column[7];
    for (int i = 0; i < 7; i++) {
        column[i] = NULL;
    }

    LinkedCard* foundation_piles[4];
    for (int i = 0; i < 4; i++) {
        foundation_piles[i] = NULL;
    }






    return 0;
}