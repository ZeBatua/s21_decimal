#include "../s21_decimal.h"

void extdec_to_binary_mass(s21_extended_decimal decimal, int *mass) {
    for (int i = 0; i < 320; i++) {
        mass[i] = get_extdec_bit(decimal, i);
    }
}
