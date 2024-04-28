#pragma once


#include <SDL_render.h>

#include "model/card.h"

#define CARD_WIDTH (240/2)
#define CARD_HEIGHT (336/2)
#define CARD_SPACING 50

typedef struct CardView CardView;

struct CardView {
    SDL_Texture *image;
    SDL_Rect *card_image_rect;
    SDL_Rect *clickable_area;
    LinkedCard *card;
    int is_selected;
    CardView *next;
    CardView *prev;
};

CardView *create_card_view(SDL_Rect *image_rect, LinkedCard *card, SDL_Renderer *renderer);

SDL_Surface *get_card_image(const LinkedCard* card);

SDL_Texture *get_card_texture(const LinkedCard* card, SDL_Renderer *renderer);

void render_card_view(CardView *card_view, SDL_Renderer *renderer);

void render_empty_card_view(SDL_Rect *rect, SDL_Renderer *renderer);

void position_card_view(CardView *card_view, int x, int y);

void destroy_card_view(CardView *card_view);

SDL_Rect *create_cardview_rect(int x, int y);

SDL_Rect *create_clickable_area(int x, int y, int is_overlayed);

void set_clickable_area(CardView *card_view, int x, int y, int is_overlayed);