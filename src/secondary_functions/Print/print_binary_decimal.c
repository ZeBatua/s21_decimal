#include "../../s21_decimal.h"

void print_binary_decimal(int mass[]) {
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass[i]);
    }
    printf("\n");
}