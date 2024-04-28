#include <controller/string_utils.h>
#include <string.h>
#include <ctype.h>


void to_upper(char* str) {
    if (str == NULL) return;
    for (int i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

int is_empty(char *str) {
    if (str == NULL) return 1;
    if (strlen(str) == 0) return 1;
    return 0;
}

void trim(char *str) {
    char *start, *end;

    // Trim leading space
    for (start = str; *start; start++) {
        if (!isspace((unsigned char)start[0]))
            break;
    }

    // Trim trailing space
    for (end = start + strlen(start); end > start; end--) {
        if (!isspace((unsigned char)end[-1]))
            break;
    }

    *end = 0;  // Set new null terminator

    // Shift the trimmed string to the start of the buffer
    if (start > str)
        memmove(str, start, end - start + 1);
}

void remove_all_spaces(char *str) {
    trim(str);
    char *i = str;
    char *j = str;
    while(*j != 0) {
        *i = *j++;
        if(*i != ' ') i++;
    }
    *i = 0;
}