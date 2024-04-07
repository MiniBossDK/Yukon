#include <core/card.h>
#include <stdio.h>

typedef struct card Linked_Card;
struct card{
    char rank;
    char suit;
    Linked_Card *next;
};

Linked_Card *createCard(char rank, char suit){
    if(validateRank(rank) && validateSuit(suit)){
        Linked_Card *card = (Linked_Card *)malloc(sizeof(Linked_Card));
        card->rank = rank;
        card->suit = suit;
        card->next = NULL;
        return card;
    }
    return NULL;
}

Linked_Card *createDeck(){
    Linked_Card *deck = NULL;
    char suits[4] = {'S', 'H', 'D', 'C'};
    char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            Linked_Card *card = createCard(ranks[j], suits[i]);
            if(deck == NULL){
                deck = card;
            }else{
                Linked_Card *temp = deck;
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = card;
            }
        }
    }
    return deck;
}

Linked_Card *createDeckFromFile(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        return NULL;
    }
    Linked_Card *deck = NULL;
    char rank, suit;
    while(fscanf(file, "%c %c\n", &rank, &suit) != EOF){
        Linked_Card *card = createCard(rank, suit);
        if(deck == NULL){
            deck = card;
        }else{
            Linked_Card *temp = deck;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = card;
        }
    }
    fclose(file);
    return deck;
}

void saveDeckToFile(Linked_Card *deck, char *fileName){
    FILE *file = fopen(fileName, "w");
    if(file == NULL){
        return;
    }
    Linked_Card *temp = deck;
    while(temp != NULL){
        fprintf(file, "%c %c\n", temp->rank, temp->suit);
        temp = temp->next;
    }
    fclose(file);
}
char[2] getCard(Linked_Card *card){
    char[2] cardStr;
    cardStr[0] = card->rank;
    cardStr[1] = card->suit;
    return cardStr;
}

void printCard(Linked_Card *card){
    printf("%c%c", card->rank, card->suit);
}

void destroyDeck(Linked_Card *deck){
    Linked_Card *temp = deck;
    while(temp != NULL){
        Linked_Card *next = temp->next;
        free(temp);
        temp = next;
    }
}

int validateRank(char rank){
    if(rank == 'A' || rank == '2' || rank == '3' || rank == '4' || rank == '5' || rank == '6' || rank == '7' || rank == '8' || rank == '9' || rank == 'T' || rank == 'J' || rank == 'Q' || rank == 'K'){
        return 1;
    }
    return 0;
}

int validateSuit(char suit){
    if(suit == 'S' || suit == 'H' || suit == 'D' || suit == 'C'){
        return 1;
    }
    return 0;
}

int validateDeck(Linked_Card *deck) {
    int ranks[13] = {0};
    int suits[4] = {0};
    Linked_Card *temp = deck;
    while (temp != NULL) {
        char rank = temp->rank;
        char suit = temp->suit;
        int rankIndex = -1;
        int suitIndex = -1;
        if (rank == 'A') {
            rankIndex = 0;
        } else if (rank == '2') {
            rankIndex = 1;
        } else if (rank == '3') {
            rankIndex = 2;
        } else if (rank == '4') {
            rankIndex = 3;
        } else if (rank == '5') {
            rankIndex = 4;
        } else if (rank == '6') {
            rankIndex = 5;
        } else if (rank == '7') {
            rankIndex = 6;
        } else if (rank == '8') {
            rankIndex = 7;
        } else if (rank == '9') {
            rankIndex = 8;
        } else if (rank == 'T') {
            rankIndex = 9;
        } else if (rank == 'J') {
            rankIndex = 10;
        } else if (rank == 'Q') {
            rankIndex = 11;
        } else if (rank == 'K') {
            rankIndex = 12;
        }
        if (suit == 'S') {
            suitIndex = 0;
        } else if (suit == 'H') {
            suitIndex = 1;
        } else if (suit == 'D') {
            suitIndex = 2;
        } else if (suit == 'C') {
            suitIndex = 3;
        }
        if (rankIndex == -1 || suitIndex == -1) {
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
}
