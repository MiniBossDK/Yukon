#include <controller/handle_game_moves.h>
#include <stdlib.h>
#include <string.h>
#include <model/column.h>
#include <model/foundation_pile.h>
#include <stdio.h>

int handle_game_move(GameMove *move, GameState *game_state) {
    // First validate if the move is valid according to the rules
    char *source_pile = (move->from->column != NULL) ? move->from->column : move->from->pile;
    LinkedCard **source = get_pile(source_pile, game_state);
    LinkedCard **destination = get_pile(move->to, game_state);
    LinkedCard *card = get_card_from_source(move->from, game_state);
    if(!validate_move(source, destination, card, game_state)) {
        return 0;
    }
    if(move->to[0] == 'F') {
        if(!validate_move_to_foundation(destination, card)) {
            strcpy(game_state->message, "Invalid move to foundation!");
            return 0;
        }
    } else if(move->to[0] == 'C') {
        if(!validate_move_to_column(destination, card)) {
            strcpy(game_state->message, "Invalid move to column!");
            return 0;
        }
    }

    int status = move_card(source, destination, card);
    if(check_win(game_state)) {
        strcpy(game_state->message, "Congratulations! You have won the game! Would you like to play again? (Y/N)");
        game_state->game_over = 1;
        return 2; // This is to prevent the default message (OK) from being displayed. We want to display the win message instead.
    }
    return status;
}

int char_to_int(const char c) {
    return c - '0';
}

int validate_move(LinkedCard **src, LinkedCard **dest, LinkedCard *card, GameState *game_state) {
    if(src == dest) {
        strcpy(game_state->message, "Source and destination is the same!");
        return 0;
    }
    if(card == NULL) {
        if(is_empty_pile(*src)) {
            strcpy(game_state->message, "Source pile is empty!");
            return 0;
        }
        strcpy(game_state->message, "Could not find card!");
        return 0;
    }
    if(!validate_move_source(src, game_state)) {
        return 0;
    }

    return 1;
}

int validate_move_source(LinkedCard **src, GameState *game_state) {

    if(is_empty_pile(*src)) {
        sprintf(game_state->message, "Source pile is empty!");
        return 0;
    }
    return 1;
}

LinkedCard **get_pile(const char* pile, GameState *game_state) {
    if(pile == NULL) {
        return NULL;
    }

    if(pile[0] == 'F') {
        return &game_state->foundation[char_to_int(pile[1]) - 1];
    } else if(pile[0] == 'C') {
        return &game_state->column[char_to_int(pile[1]) - 1];
    }
    return NULL;
}

LinkedCard* get_card_from_source(GameMoveSource* gameMoveSource, GameState *game_state) {
    if(gameMoveSource->pile != NULL) { // From here we know that the source is a foundation pile
        LinkedCard* pile = get_top_card(game_state->foundation[char_to_int(gameMoveSource->pile[1]) - 1]);
        if (pile == NULL) {
            return NULL;
        }
        return pile;
    }

    if(gameMoveSource->column != NULL) { // From here we know that the source is a column
        if(gameMoveSource->card != NULL) { // From here we know that the source is a specific card in a column
            return find_card_column(gameMoveSource->card, game_state->column[char_to_int(gameMoveSource->column[1]) - 1]);
        }
        return get_last_card(game_state->column[char_to_int(gameMoveSource->column[1]) - 1]);
    }

    return NULL;
}

int is_same_pile(LinkedCard *src, LinkedCard *dest) {
    // TODO - Make a more valid check
    return src == dest;
}

int validate_column_not_empty(LinkedCard *column) {
    return column != NULL;
}

GameMove *create_game_move(GameMoveSource *from, char *to) {
    GameMove *gameMove = malloc(sizeof(GameMove));
    gameMove->from = from;
    gameMove->to = to;
    return gameMove;
}

GameMoveSource *create_game_move_source(char *column, char *card, char *pile) {
    GameMoveSource *gameMoveSource = malloc(sizeof(GameMoveSource));
    gameMoveSource->column = column;
    gameMoveSource->card = card;
    gameMoveSource->pile = pile;
    return gameMoveSource;
}

void destroy_game_move(GameMove* move) {
    if (move == NULL) return;
    if (move->from != NULL) {
        if (move->from->column != NULL) {
            free(move->from->column);
        }
        if (move->from->card != NULL) {
            free(move->from->card);
        }
        if (move->from->pile != NULL) {
            free(move->from->pile);
        }
        free(move->from);
    }
    if (move->to != NULL) {
        free(move->to);
    }
    free(move);
}



