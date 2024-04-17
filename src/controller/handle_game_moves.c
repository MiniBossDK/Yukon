#include <controller/handle_game_moves.h>
#include <model/deck.h>
#include <view/terminal/command_parser.h>
#include <stdlib.h>
#include <string.h>

int handle_game_move(const GameMove *move, LinkedCard *column[7], LinkedCard *foundation[4], char *message) {
    if(move->from->pile != NULL) {

        return 0;
    }
    move_card(move->from->pile, move->from->column);
    return 1;
}

