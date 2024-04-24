#pragma once

#include <model/card.h>
#include <SDL.h>
#include <SDL_image.h>

typedef struct {
    SDL_Surface *image;
    SDL_Rect rect;
    LinkedCard *card;
    int is_selected;
    int x;
    int y;
    int width;
    int height;
} CardView;

CardView *create_card_view(LinkedCard *card, int x, int y);

SDL_Surface *get_card_image(const LinkedCard* card);