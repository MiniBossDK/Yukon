#include <view/gui/gui_foundation_view.h>


FoundationView *create_foundation_view(SDL_Rect *rect, int foundation_number, CardView *cards) {
    FoundationView *foundation_view = malloc(sizeof(FoundationView));
    foundation_view->rect = rect;
    foundation_view->foundation_number = foundation_number;
    foundation_view->cards = cards;
    return foundation_view;
}

FoundationView *convert_foundation_to_foundation_view(SDL_Rect* rect, int foundation_number, LinkedCard **foundation, SDL_Renderer *renderer) {
    if (foundation == NULL || *foundation == NULL) {
        return create_foundation_view(
                rect,
                foundation_number,
                NULL
                );
    }
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
    FoundationView *foundation_view = create_foundation_view(rect, foundation_number, card_view_first);

    return foundation_view;
}

void render_foundation_view(FoundationView *foundation_view, SDL_Renderer *renderer) {
    if(foundation_view == NULL) return;
    if(foundation_view->cards == NULL) {
        render_foundation_pile_placeholder(foundation_view->rect, renderer);
        return;
    }

    CardView *current = foundation_view->cards;
    while (current != NULL) {
        render_card_view(current, renderer);
        current = current->next;
    }
}

void render_foundation_pile_placeholder(SDL_Rect *foundation_rect, SDL_Renderer *renderer) {
    SDL_Rect outer_rect;
    outer_rect.x = foundation_rect->x;
    outer_rect.y = foundation_rect->y;
    outer_rect.w = 240/2;
    outer_rect.h = 336/2;
/*
    SDL_Rect inner_rect;
    outer_rect.x = foundation_rect->x + 50;
    outer_rect.y = foundation_rect->y + 50;
    outer_rect.w = 240/2 - 50;
    outer_rect.h = 336/2 - 50;
*/
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( renderer, &outer_rect );
//    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255);
//    SDL_RenderFillRect( renderer, &inner_rect );
}

SDL_Rect *create_foundationview_rect(int x, int y) {
    SDL_Rect *rect = malloc(sizeof(SDL_Rect));
    rect->x = x;
    rect->y = y;
    rect->w = CARD_WIDTH;
    rect->h = 2000; // Arbitrary height, so that the foundation can be as long as needed
    return rect;
}

