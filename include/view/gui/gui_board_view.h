#pragma once

#include <view/gui/gui_column_view.h>
#include <view/gui/gui_foundation_view.h>

typedef struct {
    ColumnView *columns;
    FoundationView *foundations;
    SDL_Rect *rect;
    int card_spacing;
} BoardView;

BoardView *create_board_view(SDL_Rect *rect, ColumnView **columns, FoundationView **foundations);

void render_board_view(BoardView *board_view, SDL_Renderer *renderer);

void destroy_board_view(BoardView *board_view);

SDL_Rect *create_boardview_rect(int x, int y);