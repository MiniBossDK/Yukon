#include <stdio.h>
#include <model/card.h>
#include <model/deck.h>

int main() {
    printf("Hello, World!\n");
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