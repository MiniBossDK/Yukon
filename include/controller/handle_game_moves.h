#pragma once

#include <model/card.h>
#include <view/terminal/command_parser.h>

int handle_game_move(const GameMove *move, LinkedCard *column[7], LinkedCard *foundation[4], char *message);