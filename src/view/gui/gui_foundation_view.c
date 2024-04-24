#include <view/gui/gui_foundation_view.h>


FoundationView *create_foundation_view(int x, int y, int width, int height, int card_spacing) {
    FoundationView *foundation_view = malloc(sizeof(FoundationView));
    foundation_view->x = x;
    foundation_view->y = y;
    foundation_view->width = width;
    foundation_view->height = height;
    foundation_view->card_spacing = card_spacing;
    foundation_view->card_count = 0;
    foundation_view->cards = malloc(sizeof(CardView) * 13);
    return foundation_view;
}