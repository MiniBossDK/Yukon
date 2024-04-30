//
// Created by Turan Talayhan on 10/04/2024.

//
#pragma once

#include "card.h"
#include "controller/game_state.h"

typedef struct GameState GameState;

LinkedCard* create_deck();

void destroy_deck(LinkedCard* deck);

int validate_deck(GameState* game_state, LinkedCard* loaded_deck);

int save_deck_to_file(LinkedCard* deck);

int save_deck_to_file_name(LinkedCard* deck, char* filename);

LinkedCard* load_deck_from_file_name(char* filename);

LinkedCard* shuffle_deck(LinkedCard* deck);

LinkedCard* split_deck(LinkedCard* deck);

LinkedCard* split_deck_int(LinkedCard* deck, int number);

LinkedCard* clone_deck(LinkedCard* deck, int hidden);