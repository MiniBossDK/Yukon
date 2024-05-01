#pragma once

#include <model/card.h>
#include <controller/game_state.h>

int validate_move_to_foundation(LinkedCard **foundation_pile, LinkedCard* moved_card);

void empty_foundations(GameState* game_state);

LinkedCard *get_top_card(LinkedCard *foundation_pile);