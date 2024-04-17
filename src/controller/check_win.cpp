//
// Created by Turan Talayhan on 17/04/2024.
//

#include "controller/check_win.h"

int check_win(LinkedCard* foundation_piles[4]) {
    for (int i = 0; i < 4; i++) {
        if (foundation_piles[i] == 0) {
            return 0;
        }
        LinkedCard* temp = foundation_piles[i];
        while (temp->next != 0) {
            if (temp->value != temp->next->value - 1 || temp->suit != temp->next->suit) {
                return 0;
            }
            temp = temp->next;
        }
    }
    return 1;
}