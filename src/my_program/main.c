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

void show_deck(LinkedCard* deck, LinkedCard* column[7]) {
    int index = 0;
    for (int i = 0; i < 52; i++) {
        if (deck != NULL) {
            if (column[index] != NULL) {
                LinkedCard* temp = column[index];
                temp = get_last_card(temp);
                LinkedCard* temp2 = deck;
                deck = deck->next;
                move_card(temp2, temp);
            } else {
                column[index] = deck;
                LinkedCard* temp = column[index];
                deck = deck->next;
                deck ->prev = NULL;
                temp->prev = NULL;
                temp->next = NULL;
            }
        }
        index++;
        if (index == 7) {
            index = 0;
        }
    }
}