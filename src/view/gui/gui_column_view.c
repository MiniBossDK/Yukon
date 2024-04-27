#include <view/gui/gui_column_view.h>
#include <view/gui/gui_card_view.h>
#include <model/column.h>

ColumnView *create_column_view(SDL_Rect *rect, int card_spacing, CardView *cards) {
    ColumnView *column_view = malloc(sizeof(ColumnView));
    column_view->rect = rect;
    column_view->card_spacing = card_spacing;
    column_view->card_count = 0;
    column_view->number = 0;
    column_view->cards = cards;
    return column_view;
}

ColumnView *convert_column_to_column_view(LinkedCard **column, SDL_Renderer *renderer) {
    LinkedCard *current = *column;
    CardView *column_view = NULL;
    while (current != NULL) {
        column_view = create_card_view(
                create_cardview_rect(0, 0),
                current,
                renderer);
        column_view = column_view->next;
        current = current->next;
    }
    return create_column_view(create_columnview_rect(0, 0), 0, column_view);
}

void render_column_view(ColumnView *column_view, SDL_Renderer *renderer) {
    for (int i = 0; i < column_view->card_count; ++i) {
        render_card_view(&column_view->cards[i], renderer);
    }
}

SDL_Rect *create_columnview_rect(int x, int y) {
    SDL_Rect *rect = malloc(sizeof(SDL_Rect));
    rect->x = x;
    rect->y = y;
    rect->w = 0;
    rect->h = 0;
    return rect;
}