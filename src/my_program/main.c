#include <stdio.h>
#include <core/add.h>
#include <core/subtract.h>
#include <core/card.h>

int main() {
    int x = 10;
    int y = 5;
    printf("x + y = %d\n", add(x, y));
    printf("x - y = %d\n", subtract(x, y));
    add_card(123456789, 1234, 1000);
    return 0;
}