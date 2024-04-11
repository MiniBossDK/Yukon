#include <stdio.h>
#include <model/card.h>
#include <model/deck.h>
#include <view/terminal/terminal_style.h>
#include <stdlib.h>

void fill_column(LinkedCard* card[7]) {
    int number_of_cards = 1;
    LinkedCard* temp;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < number_of_cards; j++) {
            if (j == 0) {
                card[i] = create_card('A', 'H');
                temp = card[i];
            } else {
                temp->next = create_card('A', 'H');
                temp = temp->next;
            }
        }
        number_of_cards = 5 + i;
    }
}

void free_column(LinkedCard* card[7]) {
    for (int i = 0; i < 7; i++) {
        LinkedCard* current = card[i];
        while (current != NULL) {
            LinkedCard* next = current->next;
            free(current);
            current = next;
        }
    }
}

void fill_foundation(LinkedCard* card[4]) {
    for (int i = 0; i < 4; i++) {
        card[i] = create_card('A', 'H');
    }
}

void free_foundation(LinkedCard* card[4]) {
    for (int i = 0; i < 4; i++) {
        LinkedCard* current = card[i];
        while (current != NULL) {
            LinkedCard* next = current->next;
            free(current);
            current = next;
        }
    }
}

int main() {

    LinkedCard* column[7];
    LinkedCard* foundation_piles[4];
    fill_column(column);
    fill_foundation(foundation_piles);

    int keepRunning = 1;
    char command[3];
    clear_terminal(1);
    while (keepRunning) {
        print_board(column, foundation_piles);
        scanf("%2s", command);
        keepRunning = 0;
    }
    free_column(column);
    free_foundation(foundation_piles);
    reset_terminal_color();

    return 0;
}



