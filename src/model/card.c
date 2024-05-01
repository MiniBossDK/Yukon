#include <model/card.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int get_suite_value(LinkedCard *card){
    if(card->suit == 'C'){
        return 0;
    } else if(card->suit == 'D') {
        return 1;
    } else if(card->suit == 'H') {
        return 2;
    } else if(card->suit == 'S') {
        return 3;
    }
    return -1;
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

int move_card(LinkedCard **source, LinkedCard **destination, LinkedCard *card) {

    // If the move is not valid, then return 0.
    if (card == NULL) return 0;
    // Unlink node from the source list
    if (card->prev) {
        card->prev->next = NULL;
        if(card->prev->hidden) {
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
    if(deck == NULL) return NULL;

    LinkedCard *temp = deck;
    while(temp->next != NULL){
        temp = temp->next;
    }
    return temp;
}