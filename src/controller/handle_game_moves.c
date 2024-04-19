#include <controller/handle_game_moves.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int handle_game_move(GameMove *move, GameState *game_state) {
    /*
    LinkedCard *source = get_card_from_source(move->from, game_state);
    if(source == NULL) {
        return 0;
    }*/
    printf("Move from: %s\n", move->from->column);
    printf("Move to: %s\n", move->to);

    LinkedCard* source = get_last_card(game_state->column[0]);
    if(source == NULL) {

        return 0;
    }

    LinkedCard *destination = get_destination_pile(move->to, game_state);

    return move_card(get_last_card(game_state->column[0]),
                     (move->to[0] == 'F') ?
                     game_state->foundation[move->to[1]] :
                     game_state->column[move->to[1]]
    );
}

int validate_move(GameMove *move, GameState *game_state) {
    if(move->from->pile != NULL) { // From here we know that the source is a foundation pile

    }

    if(move->from->column != NULL) { // From here we know that the source is a column
        if(move->from->card != NULL) { // From here we know that the source is a card
            if(!validate_card_exists_in_source(game_state->column[move->from->column[1]], move->from->card)) {
                sprintf(game_state->message, "Invalid move: %s not found in column %d", move->from->card, move->from->column[1]);
                return 0;
            }
        }
    }
    return 1;
}

LinkedCard* get_destination_pile(const char* pile, GameState *game_state) {
    if(pile == NULL) {
        return NULL;
    }

    if(pile[0] == 'F') {
        return game_state->foundation[pile[1]];
    } else if(pile[0] == 'C') {
        return game_state->column[pile[1]];
    }
    return NULL;
}

LinkedCard* get_card_from_source(GameMoveSource* gameMoveSource, GameState *game_state) {
    if(gameMoveSource->pile != NULL) { // From here we know that the source is a foundation pile
        return game_state->foundation[gameMoveSource->pile[1]];
    }

    if(gameMoveSource->column != NULL) { // From here we know that the source is a column
        if(gameMoveSource->card != NULL) { // From here we know that the source is a card
            return game_state->column[gameMoveSource->column[1]];
        }
        return get_last_card(game_state->column[gameMoveSource->column[1]]);
    }

    return NULL;
}

int execute_move() {

    return 1;
}

int validate_card_exists_in_source(LinkedCard *source, char *card) {
    LinkedCard *current = source;
    while(current != NULL) {
        char curr[2] = {current->rank, current->suit};
        if(strcmp(curr, card) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}



