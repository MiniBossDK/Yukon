#include <view/gui/event_handler.h>
#include <view/gui/snap_zone.h>

int dragging = 0;
SDL_Point mouse_pos;
CardView *dragged_card = NULL;
int drag_offset_x = 0;
int drag_offset_y = 0;
int original_x = 0;
int original_y = 0;
CardView *selected_card_stack = NULL;
SourcePile source_pile = {NULL, NULL};

int handle_event(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer) {
    switch (event->type) {
        case SDL_QUIT:
            return -1; // Special return value to indicate that the program should exit
        case SDL_MOUSEBUTTONDOWN:
            return handle_mouse_button_down(event, board_view);
        case SDL_MOUSEBUTTONUP:
            return handle_mouse_button_up(event, board_view, renderer);
        case SDL_MOUSEMOTION:
            return handle_mouse_motion(event, board_view, renderer);
    }
    return 0;
}

int handle_mouse_motion(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer) {
    mouse_pos.x = event->motion.x;
    mouse_pos.y = event->motion.y;

    if(dragging) {
        return handle_dragging(board_view, renderer);
    }

    return 1;
}

int handle_dragging(BoardView *board_view, SDL_Renderer *renderer) {
    if(dragged_card == NULL) {
        dragging = 0;
        return 0;
    }
    SDL_RenderClear(renderer);
    render_board_view(board_view, renderer);
    CardView *current = dragged_card;
    int offset_y = 0;
    while (current != NULL) {
        current->card_image_rect->x = mouse_pos.x - drag_offset_x;
        current->card_image_rect->y = mouse_pos.y - drag_offset_y + offset_y;
        offset_y += CARD_SPACING;
        render_card_view(current, renderer);
        current = current->next;
    }
    for (int i = 0; i < 7; ++i) {
        render_snap_zone(board_view->columns[i]->snap_zone, renderer);
    }
    for (int i = 0; i < 4; ++i) {
        render_snap_zone(board_view->foundations[i]->snap_zone, renderer);
    }
    SDL_RenderPresent(renderer);
    return 1;
}

int handle_mouse_button_down(SDL_Event *event, BoardView *board_view) {
    if (event->button.button != SDL_BUTTON_LEFT || dragging) return 1;

    ColumnView *clicked_column = get_column_view_at_point(&mouse_pos, board_view);
    if (clicked_column != NULL) {
        CardView *card = get_card_view_at_position(clicked_column, &mouse_pos);
        if(card == NULL) {
            return 0;
        }
        // If the card is hidden, do not allow dragging
        if(card->card->hidden) {
            return 0;
        }
        dragged_card = card;

        set_column_view_selected(card, 1);

        dragging = 1;
        drag_offset_x = mouse_pos.x - card->card_image_rect->x;
        drag_offset_y = mouse_pos.y - card->card_image_rect->y;
        original_x = card->card_image_rect->x;
        original_y = card->card_image_rect->y;

        selected_card_stack = clicked_column->cards;
        source_pile.column_view = clicked_column;
        printf("Clicked column\n");
    }
    FoundationView *clicked_foundation = get_foundation_view_at_point(board_view, &mouse_pos);
    if (clicked_foundation != NULL) {
        printf("Clicked foundation\n");
        CardView *card = get_card_view_at_position_foundation(clicked_foundation, &mouse_pos);
        if(card == NULL) {
            return 1;
        }
        dragged_card = card;
        selected_card_stack = clicked_foundation->cards;
        set_column_view_selected(card, 1);
        dragging = 1;
        drag_offset_x = mouse_pos.x - card->card_image_rect->x;
        drag_offset_y = mouse_pos.y - card->card_image_rect->y;
        original_x = card->card_image_rect->x;
        original_y = card->card_image_rect->y;
        source_pile.foundation_view = clicked_foundation;
    }
    return 1;
}

int handle_mouse_button_up(SDL_Event *event, BoardView *board_view, SDL_Renderer *renderer) {
    if (event->button.button != SDL_BUTTON_LEFT || !dragging) return 0;
    dragging = 0;
    SDL_RenderClear(renderer);

    if(dragged_card == NULL) {
        return 0;
    }

    ColumnView *dropped_column = get_dropped_column(&mouse_pos, board_view);
    FoundationView *dropped_foundation = get_dropped_foundation(&mouse_pos, board_view);

    int is_in_snap_zone = dropped_column != NULL || dropped_foundation != NULL;

    if(dropped_column != NULL && is_in_snap_zone) {
        if(dragged_card->prev != NULL) {
            remove_clickable_area(dragged_card->prev);
            set_clickable_area(dragged_card->prev,
                               dragged_card->prev->card_image_rect->x,
                               dragged_card->prev->card_image_rect->y,
                               0);
        }

        // Move the card(s) to the column
        move_card_to_column_view(dragged_card, &selected_card_stack, source_pile.column_view, dropped_column);
        // Snap the card(s) to the column
        snap_card_view_to_column(dragged_card, dropped_column->snap_zone);

        if(source_pile.foundation_view != NULL) {
            remove_foundation_snap_zone(source_pile.foundation_view);
            set_foundation_snap_zone(source_pile.foundation_view);
        } else if(source_pile.column_view != NULL) {
            remove_column_snap_zone(source_pile.column_view);
            set_column_snap_zone(source_pile.column_view);
        }
    }
    if(dropped_foundation != NULL && is_in_snap_zone) {
        if(dragged_card->prev != NULL) {
            remove_clickable_area(dragged_card->prev);
            set_clickable_area(dragged_card->prev,
                               dragged_card->prev->card_image_rect->x,
                               dragged_card->prev->card_image_rect->y,
                               0);
        }
        // Move the card to the foundation
        move_card_to_foundation_view(dragged_card, dropped_foundation);
        // Snap the card to the foundation
        snap_card_view_to_foundation(dragged_card, dropped_foundation->snap_zone);
        if(source_pile.column_view != NULL) {
            remove_column_snap_zone(source_pile.column_view);
            set_column_snap_zone(source_pile.column_view);
        }
    }

    set_column_view_selected(dragged_card, 0); // Deselect the cards
    if(!is_in_snap_zone) {
        int spacing = 0;
        CardView *current = dragged_card;
        while (current != NULL) {
            current->card_image_rect->x = original_x;
            current->card_image_rect->y = original_y + spacing;
            spacing += CARD_SPACING;
            current = current->next;
        }
    }
    render_board_view(board_view, renderer);
    SDL_RenderPresent(renderer);
    // Set new clickable area for the previous card
    //set_clickable_area(dragged_card, dragged_card->card_image_rect->x, dragged_card->card_image_rect->y, 0);
    // Set new clickable area for the card that was dragged
    dragged_card = NULL;
    selected_card_stack = NULL;

    source_pile.column_view = NULL;
    source_pile.foundation_view = NULL;

    return 1;
}