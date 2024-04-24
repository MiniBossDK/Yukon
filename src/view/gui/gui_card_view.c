#include <view/gui/gui_card_view.h>



CardView *create_card_view(int x, int y, int width, int height, LinkedCard *card) {
    CardView *card_view = malloc(sizeof(CardView));
    card_view->x = x;
    card_view->y = y;
    card_view->width = width;
    card_view->height = height;
    card_view->card = card;
    return card_view;
}

char path[30];

SDL_Surface *get_card_image(const LinkedCard* card) {
    sprintf(path, "resources/cards/%c%c.webp", card->rank, card->suit);
    return IMG_Load(path);
}