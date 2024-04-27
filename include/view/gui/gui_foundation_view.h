#pragma once

#include <view/gui/gui_card_view.h>

typedef struct FoundationView FoundationView;

struct FoundationView {
    CardView *cards;
    int foundation_number;
    SDL_Rect *rect;
};

FoundationView *create_foundation_view(SDL_Rect *rect, int card_spacing, CardView *cards);

FoundationView *convert_foundation_to_foundation_view(SDL_Rect* rect, int foundation_number, LinkedCard **foundation, SDL_Renderer *renderer);

void render_foundation_view(FoundationView *foundation_view, SDL_Renderer *renderer);

void destroy_foundation_view(FoundationView *foundation_view);

void render_foundation_pile_placeholder(SDL_Rect *foundation_rect, SDL_Renderer *renderer);

SDL_Rect *create_foundationview_rect(int x, int y);