#pragma once

typedef struct LinkedCard LinkedCard;

struct LinkedCard {
    char rank;
    char suit;
    char hidden;
    int value;
    LinkedCard* prev;
    LinkedCard* next;
};

/*
 * Create a card with the given rank and suit
 */
LinkedCard* create_card(char rank, char suit);


/*
 * Destroy a card
 */
void destroy_card(LinkedCard* card);

/*
 * Convert the card rank to an int value
 */

int card_value(LinkedCard *card);

/*
 * Hide the card
 */
void hide_card(LinkedCard *card);

/*
 * Unhide the card
 */
void unhide_card(LinkedCard *card);

/*
 * Get the card as a string
 */
char* get_card(LinkedCard *card);

/*
 * Print the card
 */
void print_card(LinkedCard *card);

/*
 * Validate the rank
 */
int validate_rank(char rank);

/*
 * Validate the suit
 */
int validate_suit(char suit);

/*
 * Get the last card in the deck
 */
LinkedCard* get_last_card(LinkedCard *deck);
