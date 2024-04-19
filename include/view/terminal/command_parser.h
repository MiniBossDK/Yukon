#pragma once

#include <controller/game_state.h>

#define MAX_ARGS 4

typedef enum {
    GAME_MOVE,
    COMMAND,
} CommandType;

typedef struct {
    char *name;
    int (*func)(char *args[MAX_ARGS], GameState* game_state);
} Command;

typedef struct {
    char *command;
    char *args[MAX_ARGS];
} ParsedCommand;

typedef struct {
    char *column;
    char *card;
    char *pile;
} GameMoveSource;

typedef struct {
    GameMoveSource *from;
    char *to;
} GameMove;

void destroy_command(ParsedCommand *command);

void destroy_game_move(GameMove *move);

int evaluate_command(ParsedCommand *command, GameState* state);

int evaluate_game_move(GameMove *move, GameState *state);

CommandType get_command_type(const char *command);

ParsedCommand* extract_command(const char *command);

GameMove* extract_game_move(const char *game_move);

int validate_startup_command(const ParsedCommand *command);

int validate_game_command(const ParsedCommand *command);

int validate_command(const ParsedCommand *command, GameState* state);

int validate_game_move_syntax(const GameMove *move, GameState *state);

int parse_command(const char *command, GameState *state);

int parse_game_move(const char* command, GameState *state);

GameMoveSource *extract_move_source(const char *source);

int validate_foundation_pile(const char *pile);

int validate_column(const char *column);

int validate_card_input(const char *card);

void trim(char *str);

void remove_all_spaces(char *str);

int is_empty(char *str);

int is_specific_card(const char *source);

int is_column(const char *column);

int is_foundation_pile(const char *pile);

void to_upper(char* str);