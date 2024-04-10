#pragma once

typedef struct LinkedCard LinkedCard;

struct LinkedCard {
    char rank;
    char suit;
    LinkedCard* next;
};

/*
 * Create a card with the given rank and suit
 */
LinkedCard* create_card(char rank, char suit);

/*
 * Create a deck of 52 cards
 */
LinkedCard* create_deck();

/*
 * Create a deck of 52 cards from a file
 */
LinkedCard* create_deck_from_file(char *fileName);

/*
 * Save a deck of cards to a file
 */
void save_deck_to_file(LinkedCard *deck, char *fileName);

char* get_card(LinkedCard *card);

void print_card(LinkedCard *card);

int validate_rank(char rank);

int validate_suit(char suit);
