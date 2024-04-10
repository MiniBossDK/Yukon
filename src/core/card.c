#include <core/card.h>
#include <stdio.h>
#include <stdlib.h>

LinkedCard* create_card(char rank, char suit) {
    if(validate_rank(rank) && validate_suit(suit)){
        LinkedCard *card = (LinkedCard *)malloc(sizeof(LinkedCard));
        card->rank = rank;
        card->suit = suit;
        card->next = NULL;
        return card;
    }
    return NULL;
}

LinkedCard *create_deck() {
    LinkedCard *deck = NULL;
    char suits[4] = {'S', 'H', 'D', 'C'};
    char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            LinkedCard *card = create_card(ranks[j], suits[i]);
            if(deck == NULL){
                deck = card;
            }else{
                LinkedCard *temp = deck;
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = card;
            }
        }
    }
    return deck;
}

LinkedCard *create_deck_from_file(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        return NULL;
    }
    LinkedCard *deck = NULL;
    char rank, suit;
    while(fscanf(file, "%c%c\n", &rank, &suit) != EOF){
        LinkedCard *card = create_card(rank, suit);
        if(deck == NULL){
            deck = card;
        }else{
            LinkedCard *temp = deck;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = card;
        }
    }
    fclose(file);
    return deck;
}

void save_deck_to_file(LinkedCard *deck, char *fileName){
    FILE *file = fopen(fileName, "w");
    if(file == NULL){
        return;
    }
    LinkedCard *temp = deck;
    while(temp != NULL) {
        fprintf(file, "%c%c\n", temp->rank, temp->suit);
        temp = temp->next;
    }
    fclose(file);
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

void destroy_deck(LinkedCard *deck){
    LinkedCard *temp = deck;
    while(temp != NULL){
        LinkedCard *next = temp->next;
        free(temp);
        temp = next;
    }
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

int validate_deck(LinkedCard *deck) {
    int ranks[13] = {0};
    int suits[4] = {0};
    LinkedCard *temp = deck;
    while (temp != NULL) {
        int rankIndex = temp->rank - 'A';
        int suitIndex = temp->suit - 'S';
        if (rankIndex < 0 || rankIndex > 12 || suitIndex < 0 || suitIndex > 3) {
            return 0;
        }
        if (ranks[rankIndex] == 1 || suits[suitIndex] == 1) {
            return 0;
        }
        ranks[rankIndex] = 1;
        suits[suitIndex] = 1;
        temp = temp->next;
    }

    for (int i = 0; i < 13; i++) {
        if (ranks[i] == 0) {
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (suits[i] == 0) {
            return 0;
        }
    }
    return 1;
}





