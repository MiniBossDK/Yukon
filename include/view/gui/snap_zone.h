#pragma once

#include <view/gui/gui_foundation_view.h>
#include <view/gui/gui_column_view.h>
#include <view/gui/gui_board_view.h>

/**
 * Sets the snap zone for the column view.
 * @param column_view
 */
void set_column_snap_zone(ColumnView *column_view);

/**
 * Sets the snap zone for the foundation view.
 * @param foundation_view
 */
void set_foundation_snap_zone(FoundationView *foundation_view);

/**
 * Set the snap zones for the columns and foundations in the board view.
 * @param board_view The board view to set the snap zones for
 */
void set_board_snap_zones(BoardView *board_view);

/**
 * Snap the card view to the snap zone.
 * @param card_view
 * @param snap_zone
 */
void snap_card_view_to_column(CardView *card_view, SDL_Rect *snap_zone);

/**
 * Remove the snap zone from the column view.
 * @param column_view
 */
void remove_column_snap_zone(ColumnView *column_view);

/**
 * Remove the snap zone from the foundation view.
 * @param foundation_view
 */
void remove_foundation_snap_zone(FoundationView *foundation_view);

/**
 * Shows the snap zone on the screen. This is useful for debugging.
 * @param snap_zone The snap zone to render
 * @param renderer The renderer to render the snap zone to
 */
void render_snap_zone(SDL_Rect *snap_zone, SDL_Renderer *renderer);

/**
 * Get the column that the card was dropped on (if any).
 * @param dropped_point The point where the card was dropped
 * @param board_view
 * @return The column that the card was dropped on, or NULL if it was not dropped on a column
 */
ColumnView *get_dropped_column(SDL_Point *dropped_point, BoardView *board_view);

/**
 * Get the foundation that the card was dropped on (if any).
 * @param dropped_point The point where the card was dropped
 * @param board_view
 * @return The foundation that the card was dropped on, or NULL if it was not dropped on a foundation
 */
FoundationView *get_dropped_foundation(SDL_Point *dropped_point, BoardView *board_view);

void snap_card_view_to_foundation(CardView *card_view, SDL_Rect *snap_zone);