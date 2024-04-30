#include <view/gui/gui_column_view.h>
#include <view/gui/gui_board_view.h>

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
        return create_column_view(
                rect,
                column_number,
                NULL
                );
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
        // Set the clickable area for the card view where most of them will be overlayed by the
        // next card except the last one
        set_clickable_area(card_view, rect->x, y_position, current_card != NULL);
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
    if(column_view->cards == NULL) return;
    CardView *current = column_view->cards;
    while (current != NULL) {
        if(current->is_selected) {
            current = current->next;
            continue;
        } else if(current->card->hidden) {
            render_empty_card_view(current->card_image_rect, renderer);
        } else {
            render_card_view(current, renderer);
        }
        current = current->next;
    }
}

SDL_Rect *create_columnview_rect(int x, int y) {
    SDL_Rect *rect = malloc(sizeof(SDL_Rect));
    rect->x = x;
    rect->y = y;
    rect->w = CARD_WIDTH;
    rect->h = 2000; // Arbitrary height, so that the column can be as long as needed
    return rect;
}

CardView *get_card_view_at_position(ColumnView *column_view, SDL_Point *point) {
    CardView *current = column_view->cards;
    while (current != NULL) {
        if(SDL_PointInRect(point, current->clickable_area)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void destroy_column_view(ColumnView *column_view) {
    CardView *current = column_view->cards;
    while (current != NULL) {
        CardView *next = current->next;
        destroy_card_view(current);
        current = next;
    }
    free(column_view->rect);
    free(column_view);
}

void move_card_to_column_view(CardView *cards, CardView **src_pile, ColumnView *sourcePile, ColumnView *dst_column_view) {

    // If the source column is the same as the destination column, do nothing
    if(*src_pile == dst_column_view->cards) return;

    if(cards->prev == NULL) {
        // if the source column is going to be empty, set the
        // destination column to the source column
        sourcePile->cards = NULL;
    } else {
        // if the source column is not going to be empty, set the next card to nothing
        cards->prev->next = NULL;
    }

    // if the destination column is empty, set the cards to the destination column
    if(dst_column_view->cards == NULL) {
        dst_column_view->cards = cards;
        return;
    }
    // Get the last card in the destination column
    CardView *last_card = get_last_card_view(dst_column_view->cards);
    // Point the first card to the last card in the destination column
    cards->prev = last_card;
    // ... and point the last card to the newly added card
    last_card->next = cards;
}

ColumnView* get_column_view_at_point(SDL_Point *point, BoardView *board_view) {
    for (int i = 0; i < 7; ++i) {
        if(board_view->columns[i]->cards == NULL) continue;
        if(SDL_PointInRect(point, board_view->columns[i]->rect)) {
            return board_view->columns[i];
        }
    }
    return NULL;
}

CardView *get_last_card_view(CardView *card_view) {
    CardView *current = card_view;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

void set_column_view_selected(CardView *card_view, int is_selected) {
    CardView *current = card_view;
    while (current != NULL) {
        current->is_selected = is_selected;
        current = current->next;
    }
}