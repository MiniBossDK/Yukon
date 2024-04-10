#include <core/card.h>
#include <stdio.h>
#include <stdlib.h>

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
    free(card);
}

int card_value(LinkedCard *card){
    if(card->rank == 'A'){
        return 1;
    } else if(card->rank == 'T' || card->rank == 'J' || card->rank == 'Q' || card->rank == 'K'){
        return 10;
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
    printf("%c%c ", card->rank, card->suit);
}

void hide_card(LinkedCard *card){
    card->hidden = 1;
}

void unhide_card(LinkedCard *card){
    card->hidden = 0;
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






