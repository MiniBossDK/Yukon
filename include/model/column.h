#pragma once

#include <model/card.h>
#include "controller/game_state.h"

int validate_move_to_column(LinkedCard* column_card, LinkedCard* moved_card);

void empty_columns(GameState* game_state);

LinkedCard* find_card_column(char* card, LinkedCard* column);