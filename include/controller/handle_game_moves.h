#pragma once

#include <model/card.h>
#include <view/terminal/command_parser.h>

typedef struct GameMove GameMove;
typedef struct GameMoveSource GameMoveSource;

struct GameMoveSource {
    char *column;
    char *card;
    char *pile;
};

struct GameMove {
    GameMoveSource *from;
    char *to;
};

GameMoveSource *create_game_move_source(char *column, char *card, char *pile);

GameMove *create_game_move(GameMoveSource *from, char *to);

void destroy_game_move(GameMove *move);

void destroy_game_move_source(GameMoveSource *source);

int handle_game_move(GameMove *move, GameState* state);

int validate_move(LinkedCard **src, LinkedCard **dest, LinkedCard *card, GameState *game_state);

LinkedCard* get_card_from_source(GameMoveSource* gameMoveSource, GameState *game_state);

LinkedCard **get_pile(const char* pile, GameState *game_state);

int validate_move_source(LinkedCard **source, GameState *game_state);

int char_to_int(char c);