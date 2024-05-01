#pragma once

#include <SDL_events.h>
#include <SDL_render.h>
#include <view/gui/gui_board_view.h>
#include <controller/game_state.h>
#include <controller/handle_game_moves.h>

typedef struct SourcePile {
    ColumnView *column_view;
    FoundationView *foundation_view;
} SourcePile;

int handle_event(SDL_Event *event, BoardView *board_view, GameState *state, SDL_Renderer *renderer);

int handle_mouse_button_down(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer);

int handle_mouse_button_up(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer);

int handle_mouse_motion(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer);

int handle_dragging(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer);

void handle_dropped_nothing(CardView *cardView);

void handle_dropped_column(CardView *cardView, ColumnView *columnView);

void handle_dropped_foundation(CardView *cardView, FoundationView *foundationView);
