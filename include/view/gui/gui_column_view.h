#pragma once

#include <model/card.h>
#include <SDL2/SDL.h>
#include <view/gui/gui_card_view.h>

typedef struct ColumnView ColumnView;

struct ColumnView {
    CardView *cards;
    int column_number;
    SDL_Rect *rect;
};

ColumnView *create_column_view(SDL_Rect *rect, int column_number, CardView *cards);

ColumnView *convert_column_to_column_view(SDL_Rect *rect, LinkedCard **column, int column_number, SDL_Renderer *renderer);

void render_column_view(ColumnView *column_view, SDL_Renderer *renderer);

void destroy_column_view(ColumnView *column_view);

SDL_Rect *create_columnview_rect(int x, int y);

