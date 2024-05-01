#pragma once

#include <view/gui/gui_column_view.h>
#include <view/gui/gui_foundation_view.h>

typedef struct BoardView BoardView;

struct BoardView {
    ColumnView *columns[7];
    FoundationView *foundations[4];
    SDL_Rect *rect;
    int card_spacing;
};

BoardView *create_board_view(SDL_Rect *rect, ColumnView *columns[], FoundationView *foundations[]);

void render_board_view(BoardView *board_view, SDL_Renderer *renderer);