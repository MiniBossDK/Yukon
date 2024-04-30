#include <stdio.h>
#include <model/card.h>
#include <model/deck.h>
#include <view/terminal/terminal_style.h>
#include <string.h>
#include <controller/game_state.h>
#include <view/terminal/command_parser.h>
#include <controller/handle_commands.h>
#include <controller/phase.h>
#include <controller/game_state.h>
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

void handle_win_game(GameState* game_state);

int main() {
    LinkedCard* column[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
  
    LinkedCard* foundation_piles[4] = {NULL, NULL, NULL, NULL};
    GameState* game_state = create_game_state(NULL, column, foundation_piles);
    
    int keep_running = 1;
    char command[20];
    while (keep_running) {
        if(game_state->game_over) {
            // We to always show the win screen until the player has chosen
            handle_win_game(game_state);
            strcpy(command, "");
            if(game_state->game_over == 1) continue;
        }
        clear_terminal(1);
        print_board(game_state->column, game_state->foundation);
        print_last_command(game_state->lastCommand);
        print_message(game_state->message);
        print_input_prompt();
        fgets(command, 50, stdin);
        int status = parse_command(command, game_state);
        fflush(stdin);

        if (status == -1) {
            keep_running = 0;
        }
    }
    reset_terminal_color();
    return 0;
}

void handle_win_game(GameState* game_state) {
    char choice[2];
    char* args[4] = {NULL, NULL, NULL, NULL};
    print_win_screen(game_state);
    fgets(choice, 2, stdin);
    if (choice[0] == 'Y' || choice[0] == 'y') {
        game_state->game_over = 0;
        switch_to_play_phase(args, game_state);
        strcpy(game_state->message, "");
    } else if (choice[0] == 'N' || choice[0] == 'n') {
        game_state->game_over = 0;
        handle_quit_game(args, game_state);
        show_deck(game_state, 1);
        strcpy(game_state->message, "Welcome to Yukon Solitaire!");
    }
    fflush(stdin);
}

