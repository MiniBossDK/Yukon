#include <view/gui/gui_board_view.h>

BoardView *create_board_view(int x, int y, int width, int height, ColumnView *columns, FoundationView *foundations) {
    BoardView *board_view = malloc(sizeof(BoardView));
    board_view->x = x;
    board_view->y = y;
    board_view->width = width;
    board_view->height = height;
    board_view->card_spacing = 10;
    for (int i = 0; i < 7; ++i) {
        board_view->columns[i] = columns[i];
    }
    for (int i = 0; i < 4; ++i) {
        board_view->foundations[i] = foundations[i];
    }
    return board_view;
}