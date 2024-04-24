#pragma once

#include <view/gui/gui_card_view.h>

typedef struct {
    CardView *cards;
    int number;
    int x;
    int y;
    int width;
    int height;
    int card_spacing;
    int card_count;
} FoundationView;

FoundationView *create_foundation_view(int x, int y, int width, int height, int card_spacing);