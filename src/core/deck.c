//
// Created by Turan Talayhan on 10/04/2024.
//

#include <core/deck.h>
#include <stdio.h>
#include <stdlib.h>

LinkedCard* create_deck() {
    LinkedCard* deck = NULL;
    char suits[4] = {'S', 'H', 'D', 'C'};
    char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            LinkedCard* card = create_card(ranks[j], suits[i]);
            if(deck == NULL){
                deck = card;
            }else{
                LinkedCard* temp = deck;
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = card;
            }
        }
    }
    return deck;
}

void destroy_deck(LinkedCard* deck){
    LinkedCard *temp = deck;
    while(temp != NULL){
        LinkedCard* next = temp->next;
        free(temp);
        temp = next;
    }
}

int validate_deck(LinkedCard* deck) {
    int ranks[13] = {0};
    int suits[4] = {0};
    LinkedCard* temp = deck;
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

int save_deck_to_file(LinkedCard* deck){
    FILE* file = fopen("cards", "w");
    if(file == NULL){
        return 0;
    }
    LinkedCard *temp = deck;
    while(temp != NULL) {
        fprintf(file, "%c%c\n", temp->rank, temp->suit);
        temp = temp->next;
    }
    fclose(file);
    return 1;
}

int save_deck_to_file_name(LinkedCard* deck, char* fileName){
    FILE* file = fopen(fileName, "w");
    if(file == NULL){
        return 0;
    }
    LinkedCard *temp = deck;
    while(temp != NULL) {
        fprintf(file, "%c%c\n", temp->rank, temp->suit);
        temp = temp->next;
    }
    fclose(file);
    return 1;
}

LinkedCard* load_deck_from_file(){
    FILE* file = fopen("cards", "r");
    if(file == NULL){
        return NULL;
    }
    LinkedCard* deck = NULL;
    char rank, suit;
    while(fscanf(file, "%c%c\n", &rank, &suit) != EOF){
        LinkedCard* card = create_card(rank, suit);
        if(deck == NULL){
            deck = card;
        }else{
            LinkedCard* temp = deck;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = card;
        }
    }
    fclose(file);
    return deck;
}

LinkedCard* load_deck_from_file_name(char* fileName){
    FILE* file = fopen(fileName, "r");
    if(file == NULL){
        return NULL;
    }
    LinkedCard* deck = NULL;
    char rank, suit;
    while(fscanf(file, "%c%c\n", &rank, &suit) != EOF){
        LinkedCard* card = create_card(rank, suit);
        if(deck == NULL){
            deck = card;
        }else{
            LinkedCard* temp = deck;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = card;
        }
    }
    fclose(file);
    return deck;
}

LinkedCard* shuffle_deck(LinkedCard* deck){
    int size = 0;
    LinkedCard* temp = deck;
    while(temp != NULL){
        size++;
        temp = temp->next;
    }
    LinkedCard* shuffledDeck = NULL;
    for(int i = 0; i < size; i++){
        LinkedCard* temp = deck;
        LinkedCard* prev = NULL;
        int random = rand() % size;
        for(int j = 0; j < random; j++){
            prev = temp;
            temp = temp->next;
        }
        if(prev == NULL){
            deck = temp->next;
        }else{
            prev->next = temp->next;
        }
        temp->next = NULL;
        if(shuffledDeck == NULL){
            shuffledDeck = temp;
        }else{
            LinkedCard* temp2 = shuffledDeck;
            while(temp2->next != NULL){
                temp2 = temp2->next;
            }
            temp2->next = temp;
        }
    }
    return shuffledDeck;
}

LinkedCard* split_deck(LinkedCard* deck){
    int size = 0;
    LinkedCard* temp = deck;
    while(temp != NULL){
        size++;
        temp = temp->next;
    }
    LinkedCard* deck1 = NULL;
    LinkedCard* deck2 = NULL;
    for(int i = 0; i < size / 2; i++){
        LinkedCard* temp = deck;
        deck = deck->next;
        temp->next = NULL;
        if(deck1 == NULL){
            deck1 = temp;
        }else{
            LinkedCard* temp2 = deck1;
            while(temp2->next != NULL){
                temp2 = temp2->next;
            }
            temp2->next = temp;
        }
    }
    deck2 = deck;
    return deck1;
}

LinkedCard* split_deck_int(LinkedCard* deck, int number){
    int size = 0;
    LinkedCard* temp = deck;
    while(temp != NULL){
        size++;
        temp = temp->next;
    }
    LinkedCard* decks[number];
    for(int i = 0; i < number; i++){
        decks[i] = NULL;
    }
    for(int i = 0; i < size; i++){
        LinkedCard* temp = deck;
        deck = deck->next;
        temp->next = NULL;
        if(decks[i % number] == NULL){
            decks[i % number] = temp;
        }else{
            LinkedCard* temp2 = decks[i % number];
            while(temp2->next != NULL){
                temp2 = temp2->next;
            }
            temp2->next = temp;
        }
    }
    return decks[0];
}