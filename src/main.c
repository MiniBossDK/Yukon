#include <stdio.h>
#include <model/card.h>
#include <model/deck.h>
#include <view/terminal/terminal_style.h>
#include <string.h>
#include <view/terminal/command_parser.h>
#include <controller/handle_commands.h>
#include <stdlib.h>
/*
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
*/
void game_init(LinkedCard **deck, LinkedCard *columns[7]);

void show_deck(LinkedCard* deck, LinkedCard* column[7]);

int main() {
    /*
    LinkedCard* column[7];
    LinkedCard* foundation_piles[4];
    fill_columns(column);
    fill_foundation_piles(foundation_piles);
     */
    int keep_running = 1;
    char command[20];
    char last_command[20];
    clear_terminal(1);
    char message[100] = "";
    while (keep_running) {
        //print_board(column, foundation_piles);
        print_last_command(last_command);
        print_message(message);
        print_input_prompt();
        fgets(command, 50, stdin);
        int status = parse_command(command, STARTUP, message, last_command);
        fflush(stdin);

        if (status == -1) {
            keep_running = 0;
        }
        clear_terminal(1);
    }
    //free_columns(column);
    //free_foundation_piles(foundation_piles);
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

