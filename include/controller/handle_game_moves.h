#pragma once

#include <model/card.h>
#include <view/terminal/command_parser.h>

int handle_game_move(const GameMove *move, GameState* state, char *message);