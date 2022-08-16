#include "s21_decimal.h"

void decimal_to_binary_mass(s21_decimal decimal, int *mass) {
    for (int i = 0; i < 128; i++) {
        mass[i] = get_decimal_bit(decimal, i);
    }
}
