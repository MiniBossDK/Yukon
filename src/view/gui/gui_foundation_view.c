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

FoundationView *convert_foundation_to_foundation_view(LinkedCard *foundation, SDL_Renderer *renderer) {
    CardView *cardView = NULL;
    LinkedCard *current = foundation;
    while (current != NULL) {
        current = current->next;
        cardView = create_card_view(create_cardview_rect(0, 0), current, renderer);
        if(current->prev != NULL) {
            cardView->prev = create_card_view(create_cardview_rect(0, 0), current->prev, renderer);
        }
        cardView = cardView->next;
    }
    return create_foundation_view(create_foundationview_rect(0, 0), 0, cardView);
}

void render_foundation_view(FoundationView *foundation_view, SDL_Renderer *renderer) {
    for (int i = 0; i < foundation_view->card_count; ++i) {
        render_card_view(&foundation_view->cards[i], renderer);
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

