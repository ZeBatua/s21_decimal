#include "../s21_decimal.h"

void print_binary_extdec(int mass[]) {
    for (int i = 319; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 320)) {
            if ((i + 1) % 160 == 0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
        printf("%d", mass[i]);
    }
    printf("\n");
}
