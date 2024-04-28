#pragma once

/**
 * Convert a string to uppercase
 * @param str The string to convert to uppercase
 */
void to_upper(char* str);

/**
 * Trim leading and trailing spaces from a string
 * @param str The string to trim
 */
void trim(char *str);

/**
 * Remove all spaces from a string
 * @param str The string to remove spaces from
 */
void remove_all_spaces(char *str);

/**
 * Check if a string is empty or NULL
 * @param str
 * @return 1 if the string is empty or NULL, 0 otherwise
 */
int is_empty(char *str);
