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
void show_deck(LinkedCard* deck, LinkedCard* column[7]) {
    LinkedCard* deck_clone = clone_deck(deck);
    int index = 0;
    LinkedCard* temp = deck_clone->next;
    for (int i = 0; i < 52; i++) {
        if (column[index] != NULL) {
            LinkedCard* temp2 = column[index];
            temp2 = get_last_card(temp2);
            temp2 -> next = deck_clone;
            deck_clone -> prev = temp2;
            deck_clone->next = NULL;
        } else {
            column[index] = deck_clone;
            column[index] -> prev = NULL;
            column[index] -> next = NULL;
        }
        temp -> prev = NULL;
        if (temp -> next != NULL) {
            deck_clone = temp;
            temp = deck_clone -> next;
        }

        index++;
        if (index == 7) {
            index = 0;
        }
    }
}

void game_init(LinkedCard **deck, LinkedCard *columns[7]);

int main() {

    LinkedCard* column[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    LinkedCard* foundation_piles[4];
    LinkedCard* deck = create_deck();
    fill_foundation_piles(foundation_piles);
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

void game_init(LinkedCard **deck, LinkedCard *columns[7]) {

    int totalCardsInColumn[7] = {1, 6, 7, 8, 9, 10, 11};
    int faceDownCards[7] = {0, 1, 2, 3, 4, 5, 6};

    for (int col = 0; col < 7; col++) {

        for (int cardNum = 0; cardNum < totalCardsInColumn[col]; cardNum++) {

            LinkedCard *currentCard = *deck;
            *deck = (*deck)->next;

            if (cardNum < faceDownCards[col]) {
                hide_card(currentCard);
            } else {
                // Otherwise, it's set as faceup.
                unhide_card(currentCard);
            }

            currentCard->next = NULL;

            if (columns[col] == NULL) {
                columns[col] = currentCard;

                currentCard->prev = NULL;
            } else {
                move_card(currentCard, get_last_card(columns[col]));
            }
        }
    }
}





