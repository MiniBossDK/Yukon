#include <controller/handle_game_moves.h>
#include <stdlib.h>
#include <string.h>
#include <model/column.h>
#include <model/foundation_pile.h>
#include <stdio.h>

int handle_game_move(GameMove *move, GameState *game_state) {
    // First validate if the move is valid according to the rules
    /*
    if(!validate_move(move, game_state)) {
        return 0;
    }
    */
    LinkedCard *card = get_card_from_source(move->from, game_state);
    if(card == NULL) {
        strcpy(game_state->message, "Invalid source!");
        return 0;
    }

    LinkedCard *destination = get_destination_pile(move->to, game_state);

    int status = move_card(&game_state->column[char_to_int(move->from->column[1]) - 1], &destination, card);
    return status;
}

int char_to_int(const char c) {
    return c - '0';
}

int validate_move(GameMove *move, GameState *game_state) {
    if(validate_move_source(move->from, game_state) == 0) {
        return 0;
    }
    //LinkedCard *source = get_card_from_source(move->from, game_state);
    //LinkedCard *destination = get_destination_pile(move->to, game_state);

    return 1;
}

int is_distinct_piles(LinkedCard *source, LinkedCard *destination) {

}

int validate_move_source(GameMoveSource *source, GameState *game_state) {

    if(source->pile != NULL) { // From here we know that the source is a foundation pile
       if(is_empty_foundation(game_state->foundation[char_to_int(source->pile[1]) - 1])) {
           sprintf(game_state->message, "Foundation pile %c is empty!", source->pile[1]);
           return 0;
       }
       return 1;
    }

    if(source->column != NULL) { // From here we know that the source is a column
        LinkedCard *column = game_state->column[char_to_int(source->column[1]) - 1];
        if(source->card != NULL) { // From here we know that the source is a card
            LinkedCard *card = find_card_column(source->card, column);
            if(card == NULL) {
                sprintf(game_state->message, "Card %s does not exist in column %c!", source->card, source->column[1]);
                return 0;
            }
            return 1;
        }
        if(is_empty_column(game_state->column[char_to_int(source->column[1]) - 1])) {
            sprintf(game_state->message, "Column %c is empty!", source->column[1]);
            return 0;
        }
        return 1;
    }

    sprintf(game_state->message, "SOMETHING WENT WRONG!");
    return 0;
}

LinkedCard* get_destination_pile(const char* pile, GameState *game_state) {
    if(pile == NULL) {
        return NULL;
    }

    if(pile[0] == 'F') {
        return game_state->foundation[char_to_int(pile[1]) - 1];
    } else if(pile[0] == 'C') {
        return game_state->column[char_to_int(pile[1]) - 1];
    }
    return NULL;
}



LinkedCard* get_card_from_source(GameMoveSource* gameMoveSource, GameState *game_state) {
    if(gameMoveSource->pile != NULL) { // From here we know that the source is a foundation pile
        LinkedCard* pile = game_state->foundation[char_to_int(gameMoveSource->pile[1]) - 1];
        if (pile == NULL) {
            return NULL;
        }
        return pile;
    }

    if(gameMoveSource->column != NULL) { // From here we know that the source is a column
        if(gameMoveSource->card != NULL) { // From here we know that the source is a specific card in a column
            return game_state->column[char_to_int(gameMoveSource->column[1]) - 1];
        }
        return get_last_card(game_state->column[char_to_int(gameMoveSource->column[1]) - 1]);
    }

    return NULL;
}

int execute_move() {

    return 1;
}

int validate_column_not_empty(LinkedCard *column) {
    return column != NULL;
}



