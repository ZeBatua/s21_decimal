#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) { // умножение, остаток деления,
    int position = 0;
    int error = 0;
    s21_decimal result = {0}; // ?
    if (dst) {
        s21_truncate(src, &result);
        src.bits[0] = *dst;
        if (getBit(src.bits[3], 31)) {
            *dst *= -1; 
        }
    } else {
        error = 1;
    }
}
