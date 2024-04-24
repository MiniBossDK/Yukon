#pragma once

#include <model/card.h>
#include <SDL2/SDL.h>
#include <view/gui/gui_card_view.h>

typedef struct {
    CardView cards[52];
    int number;
    int x;
    int y;
    int width;
    int height;
    int card_spacing;
    int card_count;
} ColumnView;

ColumnView *create_column_view(int x, int y, int width, int height, int card_spacing, LinkedCard *cards);

