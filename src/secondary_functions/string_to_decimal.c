#include "../s21_decimal.h"

void string_to_decimal(const char *str, s21_decimal *decimal) {
    int i = 0;

    init_decimal(decimal);
    for (int j = 0; j < 4; j++) {
        int k = 32 + j * 33;
        unsigned int tmp = 0;
        for (; i < k; i++) {
            tmp += ((unsigned int)str[i] - 48) * pow(2, 31 - i + 33 * j);
        }
        decimal->bits[3 - j] = tmp;
        i++;
    }
}
