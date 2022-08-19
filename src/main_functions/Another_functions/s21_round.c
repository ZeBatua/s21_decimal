#include "../../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    int bits_for_change = getScale(value);
    for (int i = 0; bits_for_change + 1 > i; i++) {
        get_decimal_bit(value);
    }
}

// округление до ближайшего целого числа 