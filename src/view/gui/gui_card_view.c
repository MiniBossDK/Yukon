#include <view/gui/gui_card_view.h>

CardView *create_card_view(SDL_Rect *image_rect, LinkedCard *card, SDL_Renderer *renderer) {
    if(card == NULL) return NULL;
    CardView *card_view = malloc(sizeof(CardView));
    card_view->image = get_card_texture(card, renderer);
    card_view->card_image_rect = image_rect;
    card_view->card = card;
    card_view->next = NULL;
    card_view->prev = NULL;
    return card_view;
}

SDL_Surface *get_card_image(const LinkedCard* card) {
    char path[30];
    sprintf(path, "resources/cards/%c%c.webp", card->rank, card->suit);
    return IMG_Load(path);
}

SDL_Surface *get_card_back_image() {
    return IMG_Load("resources/cards/EmptyCard.webp");
}

SDL_Texture *get_card_texture(const LinkedCard* card, SDL_Renderer *renderer) {
    SDL_Surface *surface = get_card_image(card);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

CardView *convert_deck_to_card_views(LinkedCard *card, SDL_Renderer *renderer) {
    /*
    LinkedCard *current = card;
    CardView *card_view = create_card_view(0, 0, 0, 0, current, renderer);;
    while (current->next != NULL) {
        if(current->prev != NULL) card_view->prev = create_card_view(0, 0, 0, 0, current->prev, renderer);
        if(current->next != NULL) card_view->next = create_card_view(0, 0, 0, 0, current->next, renderer);
        current = current->next;
        card_view = card_view->next;
    }
    return card_view;
     */
}

void render_card_view(CardView *card_view, SDL_Renderer *renderer) {
    if(card_view == NULL) return;
    SDL_RenderCopy(renderer, card_view->image, NULL, card_view->card_image_rect);
}

void render_empty_card_view(SDL_Rect *rect, SDL_Renderer *renderer) {
    SDL_Surface *surface = get_card_back_image();
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}

void position_card_view(CardView *card_view, int x, int y) {
    card_view->card_image_rect->x = x;
    card_view->card_image_rect->y = y;
}

void set_clickable_area(CardView *card_view, int x, int y, int is_overlayed) {
    card_view->clickable_area = create_clickable_area(x, y, is_overlayed);
}

void destroy_card_view(CardView *card_view) {
    SDL_DestroyTexture(card_view->image);
    free(card_view);
}

SDL_Rect *create_cardview_rect(int x, int y) {
    SDL_Rect *rect = malloc(sizeof(SDL_Rect));
    rect->x = x;
    rect->y = y;
    rect->w = CARD_WIDTH;
    rect->h = CARD_HEIGHT;
    return rect;
}

SDL_Rect *create_clickable_area(int x, int y, int is_overlayed) {
    SDL_Rect *rect = malloc(sizeof(SDL_Rect));
    rect->x = x;
    rect->y = y;
    rect->w = CARD_WIDTH;
    rect->h = CARD_HEIGHT;

    return rect;
}