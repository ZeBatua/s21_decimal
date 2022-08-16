#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    int mask = -2147483648;

    init_decimal(result);
    equate_decimal(value, result);
    result->bits[3] ^= mask;
    return 0;
}
