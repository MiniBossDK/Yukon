#pragma once

#include <view/gui/gui_card_view.h>

typedef struct FoundationView FoundationView;

struct FoundationView {
    CardView *cards;
    int number;
    SDL_Rect *rect;
    int card_spacing;
    int card_count;
};

FoundationView *create_foundation_view(SDL_Rect *rect, int card_spacing, CardView *cards);

FoundationView *convert_foundation_to_foundation_view(LinkedCard *foundation, SDL_Renderer *renderer);

void render_foundation_view(FoundationView *foundation_view, SDL_Renderer *renderer);

void destroy_foundation_view(FoundationView *foundation_view);

SDL_Rect *create_foundationview_rect(int x, int y);