#include <view/terminal/terminal_style.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// https://en.wikipedia.org/wiki/ANSI_escape_code#CSI_(Control_Sequence_Introducer)_sequences
#define CLEAR_SCREEN "\e[2J" // ANSI escape code to clear the screen
#define CURSOR_HOME "\e[2H" // ANSI escape code to move the cursor to the top-left corner
#define ORANGE_BG "\e[48;2;255;217;102m" // 256-color code for yellow background
#define BLACK_TEXT "\e[38;5;232m" // ANSI escape code for black text
#define RESET_COLOR "\e[0m"       // Resets the color to default
#define BOLD_TEXT "\e[1m"         // ANSI escape code for bold text

void set_terminal_color() {
    // ANSI escape code to set the text color
    printf("%s%s%s", BOLD_TEXT, BLACK_TEXT, ORANGE_BG);
}

void reset_terminal_color() {
    printf(RESET_COLOR);
    clear_terminal(0);
}

void clear_terminal(int with_color) {
    if(with_color) {
        set_terminal_color();
    }
    printf("%s%s", CLEAR_SCREEN, CURSOR_HOME);
}

void print_message(char* message) {
    printf("Message: %s\n", message);
}

void print_input_prompt() {
    printf("INPUT > ");
}

void print_last_command(char* command) {
    printf("LAST Command: %s\n", command);
}

void print_column_numbers() {
    for (int i = 0; i < 7; i++) {
        printf("C%d", i+1);
        if (i < 6) {
            printf("\t");
        }
    }
}

void traverse_linked_list(LinkedCard* card, void (*callback)(LinkedCard*)) {
    while (card != NULL) {
        callback(card);
        card = card->next;
    }
}

void print_foundation_numbers(int pile_number) {
    printf("\tF%d", pile_number);
}

void print_empty_card() {
    printf("  \t");
}

void print_board(LinkedCard* columns[], LinkedCard* foundation_piles[]) {
    clear_terminal(1);
    print_column_numbers();
    printf("\n\n");
    LinkedCard* tempArr[7];
    for (int i = 0; i < 7; ++i) {
        tempArr[i] = columns[i];
    }
    int cards_left = 1;
    int j = 0;
    while (cards_left || j <= 7) {
        cards_left = 0;
        for (int i = 0; i < 7; i++) {
            LinkedCard* card = tempArr[i];
            if(card == NULL) {
                print_empty_card();
                continue;
            }
            print_card(card);
            printf("\t");
            tempArr[i] = card->next;
            if(tempArr[i] != NULL) {
                cards_left = 1;
            }
        }
        if((j % 2) == 0 && j <= 6) {
            int pile = (int) floor(j / 2);
            printf("\t");
            print_card(get_top_card(foundation_piles[pile]));
            print_foundation_numbers(pile + 1);
        }
        printf("\n");
        j++;
    }
}

void print_win_screen() {
    clear_terminal(1);
    printf("Congratulations! You win!\n");
}
