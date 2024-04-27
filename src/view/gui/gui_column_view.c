#include <view/gui/gui_column_view.h>
#include <view/gui/gui_card_view.h>
#include <model/column.h>

#define CARD_SPACING 50

ColumnView *create_column_view(SDL_Rect *rect, int column_number, CardView *cards) {
    ColumnView *column_view = malloc(sizeof(ColumnView));
    column_view->rect = rect;
    column_view->column_number = column_number;
    column_view->cards = cards;
    return column_view;
}

ColumnView *convert_column_to_column_view(SDL_Rect *rect, LinkedCard **column, int column_number, SDL_Renderer *renderer) {
    if (column == NULL || *column == NULL) {
        return NULL;
    }

    int y_position = 0;
    // Save the first card in another variable to prevent it modifying the original
    LinkedCard *current_card = *column;
    // Create the first card view
    CardView *card_view = create_card_view(create_cardview_rect(rect->x, y_position),
                                           current_card,
                                           renderer);
    // Save pointer to the first node
    CardView *card_view_first = card_view;
    while (current_card != NULL) {
        // Go to the next card
        current_card = current_card->next;
        if(current_card == NULL) break;
        y_position += CARD_SPACING;
        // Go to the next card view and make a card view
        card_view->next = create_card_view(create_cardview_rect(rect->x, y_position),
                         current_card,
                         renderer);
        card_view->next->prev = card_view;
        card_view = card_view->next;
    }
    ColumnView *column_view = create_column_view(rect, column_number, card_view_first);
    return column_view;
}

void render_column_view(ColumnView *column_view, SDL_Renderer *renderer) {
    CardView *current = column_view->cards;
    while (current != NULL) {
        render_card_view(current, renderer);
        current = current->next;
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