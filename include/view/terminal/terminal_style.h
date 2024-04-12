#pragma once

#include <model/foundation_pile.h>

void set_terminal_color();

void clear_terminal(int with_color);

void print_board(LinkedCard* columns[], LinkedCard* foundation_piles[]);

/*
 * Prints the column names in the following format:
 * C1  C2  C3  C4  C5  C6  C7
 * with a tab between each column number
 */
void print_column_numbers();

void print_foundation_numbers(int pile_number);

void print_last_command(char* command);

void print_message(char* message);

void print_input_prompt();

void reset_terminal_color();

void print_empty_card();

void traverse_linked_list(LinkedCard* card, void (*callback)(LinkedCard*));