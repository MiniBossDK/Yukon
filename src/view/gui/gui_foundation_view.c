#include <view/gui/gui_foundation_view.h>


FoundationView *create_foundation_view(SDL_Rect *rect, int card_spacing, CardView *cards) {
    FoundationView *foundation_view = malloc(sizeof(FoundationView));
    foundation_view->rect = rect;
    foundation_view->card_spacing = card_spacing;
    foundation_view->card_count = 0;
    foundation_view->number = 0;
    foundation_view->cards = cards;
    return foundation_view;
}

FoundationView *convert_foundation_to_foundation_view(SDL_Rect* rect, LinkedCard **foundation, SDL_Renderer *renderer) {
    if (foundation == NULL || *foundation == NULL) {
        return NULL;
    }


    int y_position = 0;
    int card_spacing = 20;
    // Save the first card in another variable to prevent it modifying the original
    LinkedCard *current_card = *foundation;
    // Create the first card view
    CardView *card_view = create_card_view(create_cardview_rect(0, 0),
                                           current_card,
                                           renderer);
    // Save pointer to the first node
    CardView *card_view_first = card_view;
    while (current_card != NULL) {
        // Go to the next card
        current_card = current_card->next;
        if(current_card == NULL) break;
        // Go to the next card view and make a card view
        card_view->next = create_card_view(create_cardview_rect(0, 0),
                                           current_card,
                                           renderer);
        card_view->next->prev = card_view;
        card_view = card_view->next;
    }
    FoundationView *foundation_view = create_foundation_view(rect, card_spacing, card_view_first);

    return foundation_view;
}

void render_foundation_view(FoundationView *foundation_view, SDL_Renderer *renderer) {
    if(foundation_view == NULL) return;
    CardView *current = foundation_view->cards;
    while (current != NULL) {
        render_card_view(current, renderer);
        current = current->next;
    }
}

SDL_Rect *create_foundationview_rect(int x, int y) {
    SDL_Rect *rect = malloc(sizeof(SDL_Rect));
    rect->x = x;
    rect->y = y;
    rect->w = 0;
    rect->h = 0;
    return rect;
}

