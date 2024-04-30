#include <model/card.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedCard *create_card(char rank, char suit) {
        LinkedCard *card = (LinkedCard *) malloc(sizeof(LinkedCard));
        card->rank = rank;
        card->suit = suit;
        card->hidden = 0;
        card->value = card_value(card);
        card->prev = NULL;
        card->next = NULL;
        return card;
}

void destroy_card(LinkedCard *card) {
    while (card->next != NULL) {      // check the next card if it exists so condition true.
        card = card->next;            // go to the next card.
        free(card->prev);     // destroy the previous card.
    }
    free(card);               // if while condition false and there are NULL next cards then it destroy the present card.
}


int card_value(LinkedCard *card) {
    switch (card->rank) {
        case 'A':
            return 1;
        case 'T':
            return 10;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return -1;
    }
}

int get_suite_value(LinkedCard *card) {
    if (card->suit == 'C') {
        return 0;
    } else if (card->suit == 'D') {
        return 1;
    } else if (card->suit == 'H') {
        return 2;
    } else if (card->suit == 'S') {
        return 3;
    }
    return -1;
}

char *get_card(LinkedCard *card) {
    char cardStr[2];
    cardStr[0] = card->rank;
    cardStr[1] = card->suit;
    return cardStr;
}

void print_card(LinkedCard *card) {
    if (card == NULL || card->hidden) {
        printf("[]");
        return;
    }

    printf("%c%c", card->rank, card->suit);
}

void hide_card(LinkedCard *card) {
    card->hidden = 1;
}

void unhide_card(LinkedCard *card) {
    card->hidden = 0;
}

int move_card(LinkedCard **source, LinkedCard **destination, LinkedCard *card) {
    // If source is a column:card, then use find_card_column to see if the card is in the column.

    // If source is just a column, then use get_last_card to get the last card in the column.

    // If the target is a column, then use validate_move_to_column to see if the move is valid.

    // If the target is a foundation, then use validate_move_to_foundation to see if the move is valid.

    // If the move is valid, then move the card from the source to the destination.

    // If the move is not valid, then return 0.
    if (card == NULL) return 0;
    // Unlink node from the source list
    if (card->prev) {
        card->prev->next = NULL;
        if (card->prev->hidden) {
            unhide_card(card->prev);
        }
    }
    if (*source == card)
        *source = NULL;

    card->prev = NULL;

    // Append node to destination list
    if (*destination == NULL) {
        *destination = card;
    } else {
        LinkedCard *lastCard = *destination;
        while (lastCard->next != NULL) {
            lastCard = lastCard->next;
        }
        lastCard->next = card;
        card->prev = lastCard;
    }
    return 1;
}

int remove_card(char *card, LinkedCard **destination) {
    LinkedCard *current = *destination;
    while (current != NULL) {
        char curr[2] = {current->rank, current->suit};
        if (strcmp(curr, card) == 0) {
            if (current->prev == NULL) {
                *destination = current->next;
            } else {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            return 1;
        }
        current = current->next;
    }
    return 0;

}

int validate_rank(char rank) {
    char valid_ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    for (int i = 0; i < 13; i++) {
        if (rank == valid_ranks[i]) {
            return 1;
        }
    }
    return 0;
}

int validate_suit(char suit) {
    char valid_suits[4] = {'S', 'H', 'D', 'C'};
    for (int i = 0; i < 4; i++) {
        if (suit == valid_suits[i]) {
            return 1;
        }
    }
    return 0;
}

int validate_card(char rank, char suit) {
    return validate_rank(rank) && validate_suit(suit);
}

LinkedCard *get_last_card(LinkedCard *deck) {
    if (deck == NULL) return NULL;

    LinkedCard *temp = deck;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}