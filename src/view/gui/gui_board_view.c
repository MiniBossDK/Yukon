#include <view/gui/gui_board_view.h>

BoardView *create_board_view(SDL_Rect *rect, ColumnView *columns[], FoundationView *foundations[]) {
    BoardView *board_view = malloc(sizeof(BoardView));
    board_view->rect = rect;
    board_view->card_spacing = 10;
    for (int i = 0; i < 7; ++i) {
        board_view->columns[i] = columns[i];
    }
    for (int i = 0; i < 4; ++i) {
        board_view->foundations[i] = foundations[i];
    }
    return board_view;
}

void position_column_view(ColumnView *column_view, int x, int y) {

}

void position_foundation_view(FoundationView *foundation_view, int x, int y) {
    foundation_view->rect->x = x;
    foundation_view->rect->y = y;
    for (int i = 0; i < 4; ++i) {
        position_card_view(&foundation_view->cards[i], x, y + i * foundation_view->card_spacing);
    }
}

void render_board_view(BoardView *board_view, SDL_Renderer *renderer) {
    for (int i = 0; i < 7; ++i) {
        render_column_view(board_view->columns[i], renderer);
    }
    for (int i = 0; i < 4; ++i) {
        render_foundation_view(board_view->foundations[i], renderer);
    }
}