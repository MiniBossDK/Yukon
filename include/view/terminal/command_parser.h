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


/**
 * Destroy the command structure
 * @param command The command to destroy
 */
void destroy_command(ParsedCommand *command);

/**
 * Destroy the game move structure
 * @param move
 */
void destroy_game_move(GameMove *move);

/**
 * Evaluate the command and execute the corresponding function
 * @param command The command to evaluate
 * @param state The game state
 * @return 1 if the command was executed successfully, 0 otherwise
 */
int evaluate_command(ParsedCommand *command, GameState* state);

/**
 * Evaluate the game move and execute the corresponding function
 * @param move
 * @param state
 * @return
 */
int evaluate_game_move(GameMove *move, GameState *state);

/**
 * Determine the type of the command. The type is determined by
 * checking if the string contains a -> character.
 * @param command The command to determine the type of
 * @return The type of the command
 */
CommandType get_command_type(const char *command);

/**
 * Extract the command from the input string
 * @param command The input string
 * @return The parsed command
 */
ParsedCommand* extract_command(const char *command);

GameMove* extract_game_move(const char *game_move);

int validate_startup_command(const ParsedCommand *command);

int validate_game_command(const ParsedCommand *command);

int validate_command(const ParsedCommand *command, GameState* state);

/**
 * Validate the syntax of a game move
 * @param move The move to validate
 * @param state
 * @return 1 if the move is valid syntax, 0 otherwise
 */
int validate_game_move_syntax(const GameMove *move, GameState *state);

/**
 * Parses a command string and executes the corresponding function
 * @param command The command string to parse
 * @param state The game state
 * @return 1 if the command was executed successfully, 0 otherwise
 */
int parse_command(const char *command, GameState *state);

/**
 * Parses a game move command
 * @param command The string to parse
 * @param state
 * @return 1 if the command was executed successfully, 0 otherwise
 */
int parse_game_move(const char* command, GameState *state);

/**
 * Extract the move source from the string
 * @param source The source string
 * @return The parsed move source
 */
GameMoveSource *extract_move_source(const char *source);

/**
 * Validates
 * @param pile
 * @return
 */
int validate_foundation_pile(const char *pile);

int validate_column(const char *column);

int validate_card_input(const char *card);

int is_specific_card(const char *source);

int is_column(const char *column);

int is_foundation_pile(const char *pile);

