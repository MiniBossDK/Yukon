#include <model/card.h>
#include <stdio.h>
#include <stdlib.h>
#include <model/column.h>
#include <model/foundation_pile.h>

LinkedCard* create_card(char rank, char suit) {
    if(validate_rank(rank) && validate_suit(suit)){
        LinkedCard *card = (LinkedCard *)malloc(sizeof(LinkedCard));
        card->rank = rank;
        card->suit = suit;
        card->hidden = 0;
        card->value = card_value(card);
        card->prev = NULL;
        card->next = NULL;
        return card;
    }
    return NULL;
}

void destroy_card(LinkedCard* card){
     while(card->next != NULL) {      // check the next card if it exists so condition true.
        card = card->next;            // go to the next card.
        free(card->prev);     // destroy the previous card.
    }
    free(card);               // if while condition false and there are NULL next cards then it destroy the present card.
}


int card_value(LinkedCard *card){
    if(card->rank == 'A'){
        return 1;
    } else if(card->rank == 'T'){
        return 10;
    }else if(card->rank == 'J') {
        return 11;
    } else if(card->rank == 'Q') {
        return 12;
    } else if(card->rank == 'K') {
        return 13;
    } else {
        return card->rank - '0';
    }
}

char* get_card(LinkedCard *card){
    char cardStr[2];
    cardStr[0] = card->rank;
    cardStr[1] = card->suit;
    return cardStr;
}

void print_card(LinkedCard *card){
    if(card == NULL || card->hidden) {
        printf("[]");
        return;
    }

    printf("%c%c", card->rank, card->suit);
}

void hide_card(LinkedCard *card){
    card->hidden = 1;
}

void unhide_card(LinkedCard *card){
    card->hidden = 0;
}

int move_card(LinkedCard *card, LinkedCard *destination){
    // If source is a column:card, then use find_card_column to see if the card is in the column.

// If source is just a column, then use get_last_card to get the last card in the column.

// If the target is a column, then use validate_move_to_column to see if the move is valid.

// If the target is a foundation, then use validate_move_to_foundation to see if the move is valid.

// If the move is valid, then move the card from the source to the destination.

// If the move is not valid, then return 0.



    return 1;
}

int validate_rank(char rank){
    char valid_ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    for(int i = 0; i < 13; i++){
        if(rank == valid_ranks[i]){
            return 1;
        }
    }
    return 0;
}

int validate_suit(char suit){
    char valid_suits[4] = {'S', 'H', 'D', 'C'};
    for(int i = 0; i < 4; i++){
        if(suit == valid_suits[i]){
            return 1;
        }
    }
    return 0;
}

int validate_card(char rank, char suit){
    return validate_rank(rank) && validate_suit(suit);
}

LinkedCard* get_last_card(LinkedCard* deck) {
    while(deck->next != NULL){
        deck = deck->next;
    }
    return deck;
}