#pragma once

#include <model/card.h>
#include <view/terminal/command_parser.h>

int handle_game_move(GameMove *move, GameState* state);

int validate_move(GameMove *move, GameState *game_state);

int execute_move();

LinkedCard* get_card_from_source(GameMoveSource* gameMoveSource, GameState *game_state);

LinkedCard* get_destination_pile(const char* pile, GameState *game_state);

int validate_move_source(GameMoveSource *source, GameState *game_state);

int char_to_int(char c);