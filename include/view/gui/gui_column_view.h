#pragma once

#include <model/card.h>
#include <SDL2/SDL.h>
#include <view/gui/gui_card_view.h>

typedef struct {
    CardView cards[52];
    int number;
    SDL_Rect *rect;
    int card_spacing;
    int card_count;
} ColumnView;

ColumnView *create_column_view(SDL_Rect *rect, int card_spacing, CardView *cards);

ColumnView *convert_column_to_column_view(LinkedCard *column, SDL_Renderer *renderer);

void render_column_view(ColumnView *column_view, SDL_Renderer *renderer);

void destroy_column_view(ColumnView *column_view);

SDL_Rect *create_columnview_rect(int x, int y);

