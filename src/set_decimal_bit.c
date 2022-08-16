#include "s21_decimal.h"

void set_decimal_bit(s21_decimal *decimal, int bait, int position, int value) { // мб чар
    int a = pow(2, position % 32);
    if (value == 1) {
        if (get_decimal_bit(*decimal, position) == 0) {
            decimal->bits[bait] += a;
        }
    }  else if (value == 0) {
        if (get_decimal_bit(*decimal, position) == 1) {
            decimal->bits[bait] -= a;
        }
    }
}
