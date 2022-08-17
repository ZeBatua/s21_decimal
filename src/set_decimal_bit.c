#include "s21_decimal.h"

void set_decimal_bit(s21_decimal *decimal, int bait, int position, int value) { // мб чар
    if (value == 1) {
        if (get_decimal_bit(*decimal, position) == 0) {
            int mask = 1;
            mask = mask << position;
            decimal->bits[bait] |= mask;
        }
    }  else if (value == 0) {
        if (get_decimal_bit(*decimal, position) == 1) {
            int mask = 1;
            mask = mask << position;
            mask = ~mask;
            decimal->bits[bait] &= mask;
        }
    }
}
