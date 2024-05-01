#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <model/deck.h>
#include <string.h>

LinkedCard* create_deck() {
    LinkedCard* deck = NULL;
    char suits[4] = {'C', 'D', 'H', 'S'};
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

void destroy_deck(LinkedCard* deck) {
    LinkedCard* temp = deck;
    while(temp != NULL){
        LinkedCard* next = temp->next;
        free(temp);
        temp = next;
    }
}


int validate_deck(GameState* game_state, LinkedCard* loaded_deck) {
    int card_counts[4][14] = {0}; // Initialize all counts to 0
    int line_number = 1;
    LinkedCard* temp = loaded_deck;
    while (temp != NULL) {
        int rankIndex = card_value(temp);
        int suitIndex = get_suite_value(temp);
        if (rankIndex == -1) {
            sprintf(game_state->message, "Error: Invalid rank on line: %d", line_number);
            return 0; // Invalid rank
        }
        if(suitIndex == -1){
            sprintf(game_state->message, "Error: Invalid suit on line: %d", line_number);
            return 0; // Invalid suit
        }
        if (card_counts[suitIndex][rankIndex] == 1) {
            sprintf(game_state->message, "Error: Duplicate card on line: %d", line_number);
            return 0; // Duplicate card
        }
        card_counts[suitIndex][rankIndex] = 1; // Mark this card as found
        temp = temp->next;
        line_number++;
    }

    if (line_number-1 != 52){
        sprintf(game_state->message, "Error: Incorrect number of cards in deck");
        return 0; // Incorrect number of cards
    }
    return 1; // All cards are present exactly once
}

int save_deck_to_file(LinkedCard* deck){
    FILE* file = fopen("cards.txt", "w");
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

LinkedCard* load_deck_from_file_name(char* fileName){
    FILE* file = fopen(fileName, "r"); //read file
    if(file == NULL){
        return NULL;
    }
    LinkedCard* deck = NULL;
    char rank, suit;
    while(fscanf(file, "%c%c\n", &rank, &suit) != EOF){
        LinkedCard* card = create_card(rank, suit);
        //hide_card(card);
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
    LinkedCard* temp = deck->next; //Store next card in deck
    LinkedCard* shuffled_deck = deck; //Deck which will be returned
    LinkedCard* shuffled_deck_start = shuffled_deck; //Used to keep track of start of linked list
    shuffled_deck->next = NULL;  //Detach first card from deck
    deck = temp; //Set deck to next card
    deck->prev = NULL; //Remove first card from deck
    srand((unsigned)clock()); //Seed random number generator with clock
    int random;
    int max_rand = 1; //Upper limit for random number equal to current number of cards in shuffled deck
    while(1){
        temp = deck->next; //Store next card in deck
        random = rand() % max_rand; //Generate random number between 0 and max_rand
        if (random > 0 && random < max_rand) {
            for(int i = 0; i < random; i++) {
                shuffled_deck = shuffled_deck->next; //Move shuffled deck pointer to random position
            }
        }
        if(random == 0) { //if random number is 0, insert card at start of shuffled deck
            deck->next = shuffled_deck;
            shuffled_deck->prev = deck;
            if(temp != NULL) {
                temp->prev = NULL;
            }
            shuffled_deck_start = deck;
        }
        else if(random == max_rand) { //if random number is max_rand, insert card at end of shuffled deck
            deck->prev = shuffled_deck;
            shuffled_deck->next = deck;
            if(temp != NULL) {
                temp->prev = NULL;
            }
        }
        else { //insert card in middle of shuffled deck, so that the position of the card in the linked list is equal to random number
            LinkedCard* temp2 = shuffled_deck->prev;
            deck->prev = temp2;
            temp2->next = deck;
            deck->next = shuffled_deck;
            shuffled_deck->prev = deck;
            if(temp != NULL) {
                temp->prev = NULL;
            }
        }
        if(temp == NULL) {
            break; //exit while loop when deck is empty
        }
        deck = temp; //set deck to next card
        if(deck->next != NULL) {
            temp = deck-> next; //store next card in deck
        }
        else {
            temp = NULL;
        }
        shuffled_deck = shuffled_deck_start; //reset shuffled deck pointer to start of linked list
        max_rand++; //increment max_rand
    }
    return shuffled_deck_start;

}


LinkedCard* split_deck(LinkedCard* deck) {
    srand((unsigned) clock()); //Seed random number generator with clock
    int random = 1 + rand() % 51; //Generate random number between 1 and 51
    return split_deck_int(deck, random);
}


LinkedCard* split_deck_int(LinkedCard* deck, int number){
    LinkedCard* merged_deck = NULL;
    LinkedCard* temp_deck = NULL;
    LinkedCard* temp_deck_start = NULL; //Used to keep track of start of linked list
    LinkedCard* merged_deck_start = NULL; //Used to keep track of start of linked list
    for (int i = 0; i < number; i++) { //Split deck at random number
        if (i == 0) {
            temp_deck = deck;
            temp_deck_start= temp_deck;
            deck = deck -> next;
            temp_deck -> next = NULL;
            deck -> prev = NULL;
        } else {
            temp_deck -> next = deck;
            deck -> prev = temp_deck;
            temp_deck = deck;
            deck = deck -> next;
            deck -> prev = NULL;
            temp_deck -> next = NULL;
        }
    }
    temp_deck = temp_deck_start;
    merged_deck = deck;
    merged_deck_start = merged_deck;
    if (deck->next != NULL) {
        deck = deck -> next;
        deck -> prev = NULL;
        merged_deck -> next = NULL;
    }
    else {
        deck = NULL;
    }
    while(1) {
        if(temp_deck != NULL) {
            merged_deck -> next = temp_deck;
            temp_deck -> prev = merged_deck;
            temp_deck = temp_deck -> next;
            merged_deck = merged_deck -> next;
            if (temp_deck != NULL) {
                temp_deck -> prev = NULL;
            }
            merged_deck -> next = NULL;
        }
        if(deck != NULL) {
            merged_deck -> next = deck;
            deck -> prev = merged_deck;
            deck = deck -> next;
            merged_deck = merged_deck -> next;
            if (deck != NULL) {
                deck -> prev = NULL;
            }
            merged_deck -> next = NULL;
        }
        if (deck == NULL && temp_deck == NULL) {
            break;
        }
    }
    destroy_deck(temp_deck);
    destroy_deck(deck);
    merged_deck = merged_deck_start;
    return merged_deck;

}

LinkedCard* clone_deck(LinkedCard* deck, int hidden){
    LinkedCard* clone = NULL;
    LinkedCard* temp = deck;
    while(temp != NULL){
        LinkedCard* card = create_card(temp->rank, temp->suit);
        if (hidden == 1) {
            hide_card(card);
        }
        if(clone == NULL){
            clone = card;
        }else{
            LinkedCard* temp2 = clone;
            while(temp2->next != NULL){
                temp2 = temp2->next;
            }
            temp2->next = card;
        }
        temp = temp->next;
    }
    return clone;
}