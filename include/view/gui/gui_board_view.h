#pragma once

#include <view/gui/gui_column_view.h>
#include <view/gui/gui_foundation_view.h>

typedef struct {
    ColumnView columns[7];
    FoundationView foundations[4];
    int x;
    int y;
    int width;
    int height;
    int card_spacing;
} BoardView;

BoardView *create_board_view(int x, int y, int width, int height, ColumnView *columns, FoundationView *foundations);