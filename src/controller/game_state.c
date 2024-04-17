#include <controller/game_state.h>
#include <stdlib.h>
#include <string.h>


GameState* create_game_state(LinkedCard* deck, LinkedCard* columns[7], LinkedCard* foundation[4]) {
    GameState* game_state = (GameState*)malloc(sizeof(GameState));
    game_state->deck = deck;
    game_state->game_over = 0;
    for(int i = 0; i < 7; i++) {
        game_state->column[i] = columns[i];
    }

    for(int i = 0; i < 4; i++) {
        game_state->foundation[i] = foundation[i];
    }
    game_state->phase = 0;
    strcpy(game_state->message, "Hell");
    strcpy(game_state->lastCommand, "Hell");
    return game_state;
}

int check_win(GameState* game_state) {
    for (int i = 0; i < 4; i++) {
        if (game_state -> foundation[i] == NULL) {
            return 0;
        }
        if (game_state -> foundation[i]-> rank != 'K') {
            return 0;
        }
    }
    return 1;
}

void destroy_game_state(GameState* game_state) {
    free(game_state);
}

void show_deck(GameState* game_state) {
    LinkedCard* deck_clone = clone_deck(game_state->deck);
    int index = 0;
    LinkedCard* temp = deck_clone->next;
    for (int i = 0; i < 52; i++) {
        if (game_state->column[index] != NULL) {
            LinkedCard* temp2 = game_state->column[index];
            temp2 = get_last_card(temp2);
            temp2 -> next = deck_clone;
            deck_clone -> prev = temp2;
            deck_clone->next = NULL;
        } else {
            game_state->column[index] = deck_clone;
            game_state->column[index] -> prev = NULL;
            game_state->column[index] -> next = NULL;
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
        if (index == 7) {
            index = 0;
        }
    }
    deck_clone = NULL;
    destroy_deck(deck_clone);
}

void game_init(GameState* game_state) {

    LinkedCard* deck_clone = clone_deck(game_state->deck);
    LinkedCard* column[7];
    for(int i = 0; i < 7; i++) {
        column[i] = game_state->column[i];
    }
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