#include <core/card.h>
#include <stdio.h>

typedef struct card Linked_Card;
struct card{
    char rank;
    char suit;
    Linked_Card *next;
};

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
