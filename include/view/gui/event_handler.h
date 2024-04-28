#pragma once

#include <SDL_events.h>
#include <SDL_render.h>
#include <view/gui/gui_board_view.h>

int handle_event(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer);

int handle_mouse_button_down(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer);

int handle_mouse_button_up(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer);

int handle_mouse_motion(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer);

int handle_dragging(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer);
