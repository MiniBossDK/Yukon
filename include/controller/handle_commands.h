#pragma once
#include <controller/game_state.h>

int handle_load_game(char* args[4], GameState* game_state);

int handle_save_game(char* args[4], GameState* game_state);

int handle_load_deck(char* args[4], GameState* game_state);

int handle_save_deck(char* args[4], GameState* game_state);

int handle_random_shuffle_deck(char* args[4], GameState* game_state);

int handle_quit_application(char* args[4], GameState* game_state);

int handle_quit_game(char* args[4], GameState* game_state);

int handle_split_deck(char* args[4], GameState* game_state);

int handle_show_cards(char* args[4], GameState* game_state);

int switch_to_play_phase(char* args[4], GameState* game_state);

int switch_to_start_phase(char* args[4], GameState* game_state);

int handle_shuffle_deck(char* args[4], GameState* game_state);

int handle_show_deck(char* args[4], GameState* game_state);

int validate_deck_loaded(GameState* state);

int validate_max_args(char* args[4], GameState* state, int max_args);