#pragma once

#include <view/gui/gui_card_view.h>

typedef struct BoardView BoardView; // Forward declaration

typedef struct FoundationView FoundationView;

struct FoundationView {
    CardView *cards;
    int foundation_number;
    SDL_Rect *view_rect;
    SDL_Rect *snap_zone;
    SDL_Rect *clickable_area;
};

/**
 * Create a foundation view.
 * @param rect the rectangle to that the foundation view is contained in
 * @param card_spacing the spacing between the cards
 * @param cards the cards in the foundation
 * @return The foundation view
 */
FoundationView *create_foundation_view(SDL_Rect *rect, int card_spacing, CardView *cards);

/**
 * Convert a foundation to a foundation view.
 * @param rect the rectangle to that the foundation view is contained in
 * @param foundation_number The number of the foundation
 * @param foundation The foundation to convert
 * @param renderer The renderer to render the foundation view to
 * @return The converted foundation view
 */
FoundationView *convert_foundation_to_foundation_view(SDL_Rect* rect, int foundation_number, LinkedCard **foundation, SDL_Renderer *renderer);

/**
 * Renders the foundation view and all the cards in it. If the foundation view is empty, a placeholder is rendered.
 * @param foundation_view The foundation view to render
 * @param renderer The renderer to render the foundation view to
 */
void render_foundation_view(FoundationView *foundation_view, SDL_Renderer *renderer);

/**
 * Destroys the foundation view.
 * @param foundation_view The foundation view to destroy
 */
void destroy_foundation_view(FoundationView *foundation_view);

/**
 * Get the card view at the given point in the foundation view.
 * @param foundation_rect
 * @param renderer
 */
void render_foundation_pile_placeholder(SDL_Rect *foundation_rect, SDL_Renderer *renderer);

/**
 * Create a rectangle for the foundation view.
 * @param x The x position of the foundation view
 * @param y The y position of the foundation view
 * @return The rectangle for the foundation view
 */
SDL_Rect *create_foundationview_rect(int x, int y);

void move_card_to_foundation_view(CardView *card_view, FoundationView *foundation_view);

FoundationView *get_foundation_view_at_point(BoardView *board_view, SDL_Point *point);

CardView *get_card_view_at_position_foundation(FoundationView *foundation_view, SDL_Point *point);