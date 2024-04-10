#include <stdio.h>
#include <core/card.h>
#include <core/deck.h>

int main() {
    LinkedCard *deck = create_deck();
    LinkedCard *deck_copy = deck;

    LinkedCard *column[7];
    for (int i = 0; i < 7; i++) {
        column[i] = NULL;
    }


    LinkedCard *foundation_piles[4];
    for (int i = 0; i < 4; i++) {
        foundation_piles[i] = NULL;
    }
}

    void game_init(LinkedCard* deck, LinkedCard* column[7]) {
      int  num_cards = 52;
        for (int i = 0; i < num_cards; i++) {

            //flyt card

            if (current == 6) {
                if (i == 6 || i == 36 || i == 41 || i == 45 || i == 47 ||i == 50 || i == 51 ){
                    startArr++;
                }
                current == startArr;

            }


        }
    }
/*
 * for hide cards in every column
 * int 1-index
 * <=0
 * 2-index
 * <=0.......
 */


/*måske vi kan brug den :
 * move(deck, column[0])
 * while (deck ! = NULL)
 * for(int i =1, i < number-Of-Columns; i++)
 * move(deck, column[i]
 * ......................
 *
 *
 */





void show_deck(LinkedCard* deck, LinkedCard* column[7]) {
    int index = 0;
    for (int i = 0; i < 52; i++) {
        if (deck != NULL) {
            if (column[index] != NULL) {
                LinkedCard* temp = column[index];
                temp = get_last_card(temp);
                LinkedCard* temp2 = deck;
                deck = deck->next;
                deck -> prev = NULL;
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