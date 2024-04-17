#include <controller/check_win.h>
#include <stdlib.h>

int check_win(LinkedCard* foundation_piles[4]) {
    for (int i = 0; i < 4; i++) {
        if (foundation_piles[i] == NULL) {
            return 0;
        }
        if (foundation_piles[i]->rank != 'K') {
            return 0;
        }
    }
    return 1;
}