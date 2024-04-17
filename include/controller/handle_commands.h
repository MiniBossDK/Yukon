#pragma once
#include <controller/game_state.h>

int handle_load_game(char* args[4], char* message, GameState* game_state);

int handle_save_deck(char* args[4], char* message, GameState* game_state);

int handle_random_shuffle_deck(char* args[4], char* message, GameState* game_state);

int handle_quit_application(char* args[4], char* message, GameState* game_state);

int handle_quit_game(char* args[4], char* message, GameState* game_state);

int handle_split_deck(char* args[4], char* message, GameState* game_state);

int handle_show_cards(char* args[4], char* message, GameState* game_state);

int switch_to_play_phase(char* args[4], char* message, GameState* game_state);