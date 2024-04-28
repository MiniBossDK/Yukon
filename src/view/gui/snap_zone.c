#include <view/gui/snap_zone.h>


void set_column_snap_zone(ColumnView *column_view) {
    if(column_view->cards == NULL) {
        // FIXME: Replace magic numbers with constants
        column_view->snap_zone = create_cardview_rect((column_view->column_number - 1) * ((240/2)+20), 0);
        return;
    }
    CardView *current = column_view->cards;
    while (current->next != NULL) {
        current = current->next;
    }
    column_view->snap_zone = create_cardview_rect(current->card_image_rect->x, current->card_image_rect->y + CARD_SPACING);
}

void remove_column_snap_zone(ColumnView *column_view) {
    if(column_view->snap_zone == NULL) return;
    free(column_view->snap_zone);
    column_view->snap_zone = NULL;
}

void set_foundation_snap_zone(FoundationView *foundation_view) {
    foundation_view->snap_zone = create_cardview_rect(foundation_view->view_rect->x, foundation_view->view_rect->y);
}

void remove_foundation_snap_zone(FoundationView *foundation_view) {
    if(foundation_view->snap_zone == NULL) return;
    free(foundation_view->snap_zone);
    foundation_view->snap_zone = NULL;
}

void set_board_snap_zones(BoardView *board_view) {
    for (int i = 0; i < 7; ++i) {
        set_column_snap_zone(board_view->columns[i]);
    }
    for (int i = 0; i < 4; ++i) {
        set_foundation_snap_zone(board_view->foundations[i]);
    }
}

void snap_card_view_to_column(CardView *card_view, SDL_Rect *snap_zone) {
    CardView *current = card_view;
    while (current != NULL) {
        current->card_image_rect->x = snap_zone->x;
        current->card_image_rect->y = snap_zone->y;
        snap_zone->y += CARD_SPACING;
        current = current->next;
    }
}

void snap_card_view_to_foundation(CardView *card_view, SDL_Rect *snap_zone) {
    card_view->card_image_rect->x = snap_zone->x;
    card_view->card_image_rect->y = snap_zone->y;
    set_clickable_area(card_view, snap_zone->x, snap_zone->y, 0);
}

ColumnView *get_dropped_column(SDL_Point *dropped_point, BoardView *board_view) {
    for (int i = 0; i < 7; ++i) {
        if(board_view->columns[i]->snap_zone != NULL) {
            if(SDL_PointInRect(dropped_point, board_view->columns[i]->snap_zone)) {
                return board_view->columns[i];
            }
        }
    }
    return NULL;
}

FoundationView *get_dropped_foundation(SDL_Point *dropped_point, BoardView *board_view) {
    for (int i = 0; i < 4; ++i) {
        if(board_view->foundations[i]->snap_zone != NULL) {
            if(SDL_PointInRect(dropped_point, board_view->foundations[i]->snap_zone)) {
                return board_view->foundations[i];
            }
        }
    }
    return NULL;
}

void render_snap_zone(SDL_Rect *snap_zone, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, snap_zone);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

