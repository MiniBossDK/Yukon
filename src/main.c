#include <stdio.h>
#include <model/card.h>
#include <model/deck.h>
#include <view/terminal/terminal_style.h>
#include <stdlib.h>

void fill_columns(LinkedCard *card[7]) {
    int number_of_cards = 1;
    int hidden_cards = 0;
    LinkedCard* temp;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < number_of_cards; j++) {
            if (j == 0) {
                card[i] = create_card('5', 'H');
                temp = card[i];
            } else {
                temp->next = create_card('A', 'H');
                temp = temp->next;
            }
            if((hidden_cards - j) > 0) {
                hide_card(temp);
            }
        }
        number_of_cards = 6 + i;
        hidden_cards++;
    }
}

void free_columns(LinkedCard *card[7]) {
    for (int i = 0; i < 7; i++) {
        LinkedCard* current = card[i];
        while (current != NULL) {
            LinkedCard* next = current->next;
            free(current);
            current = next;
        }
    }
}

void fill_foundation_piles(LinkedCard *card[4]) {
    for (int i = 0; i < 4; i++) {
        card[i] = create_card('A', 'H');
    }
}

void free_foundation_piles(LinkedCard *card[4]) {
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
    fill_columns(column);
    fill_foundation_piles(foundation_piles);
    int keepRunning = 1;
    char command[3];
    clear_terminal(1);
    while (keepRunning) {
        print_board(column, foundation_piles);
        print_last_command("N/A");
        print_message("OK");
        print_input_prompt();
        scanf("%2s", command);
        if (command[0] == 'q') {
            keepRunning = 0;
        }
    }
    free_columns(column);
    free_foundation_piles(foundation_piles);
    reset_terminal_color();
    return 0;
}



