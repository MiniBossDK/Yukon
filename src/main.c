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
void game_init(LinkedCard *deck, LinkedCard *column[7]) {

    LinkedCard* deck_clone = clone_deck(deck);
    int index = 0;
    int start_index = 0;
    int end_index = 6;
    int hide_index = 0;

    LinkedCard* temp = deck_clone->next;
    for (int i = 0; i < 52; i++) {
        if (column[index] != NULL) {
            LinkedCard* temp2 = column[index];
            temp2 = get_last_card(temp2);
            temp2 -> next = deck_clone;
            deck_clone -> prev = temp2;
            deck_clone->next = NULL;
            if (index > hide_index) {
                hide_card(deck_clone);
            }
        } else {
            column[index] = deck_clone;
            if(index > 0) {
                hide_card(column[index]);
            }
            column[index] -> prev = NULL;
            column[index] -> next = NULL;
        }
        temp -> prev = NULL;
        if (temp -> next != NULL) {
            temp -> prev = NULL;
            deck_clone = temp;
            temp = deck_clone -> next;
        }
        else {
            deck_clone = temp;
        }

        index++;
        if (i == 6 || i == 36 || i == 41 || i == 45 || i == 48 || i == 50 ) {
            start_index++;
        }
        if (index > end_index) {
            index = start_index;
            hide_index++;
        }

    }
    deck_clone = NULL;
    destroy_deck(deck_clone);
}


int main() {
    LinkedCard* column[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
  
    LinkedCard* foundation_piles[4];
    LinkedCard* deck = create_deck();
    show_deck(deck, column);
    //fill_columns(column);
    //fill_foundation_piles(foundation_piles);
     
    int keep_running = 1;
    char command[20];
    char last_command[20];
    clear_terminal(1);
    char message[100] = "";
    GameState state = STARTUP;
    while (keep_running) {
        print_board(column, foundation_piles);
        print_last_command(last_command);
        print_message(message);
        print_input_prompt();
        fgets(command, 50, stdin);
        int status = parse_command(command, state, message, last_command);
        fflush(stdin);

        if (status == -1) {
            keep_running = 0;
        }
        if(status == -2) {
            state = PLAY;
        }
        if(status == -3) {
            state = STARTUP;
        }
        clear_terminal(1);
    }
    //free_columns(column);
    //free_foundation_piles(foundation_piles);
    reset_terminal_color();
    return 0;
}




