#pragma once

#include <view/gui/gui_card_view.h>

typedef struct BoardView BoardView; // Forward declaration

typedef struct {
    CardView *cards;
    int column_number;
    SDL_Rect *rect;
    SDL_Rect *snap_zone;
} ColumnView;

ColumnView *create_column_view(SDL_Rect *rect, int column_number, CardView *cards);

ColumnView *convert_column_to_column_view(SDL_Rect *rect, LinkedCard **column, int column_number, SDL_Renderer *renderer);

void render_column_view(ColumnView *column_view, SDL_Renderer *renderer);

SDL_Rect *create_columnview_rect(int x, int y);

CardView *get_card_view_at_position(ColumnView *column_view, SDL_Point *point);

void set_column_view_selected(CardView *card_view, int is_selected);

void move_card_to_column_view(CardView *cards, CardView **src_pile, ColumnView *sourcePile, ColumnView *dst_column_view);

CardView *get_last_card_view(CardView *card_view);

/**
 * Get the column view at the given point in the board view.
 * @param point The point to get the column view at
 * @param board_view The board view to get the column view from
 * @return The column view at the given point, or NULL if there is no column view at the given point
 */
ColumnView* get_column_view_at_point(SDL_Point *point, BoardView *board_view);

