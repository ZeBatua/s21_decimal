#include "s21_decimal.h"

void shift_left(s21_decimal *x2_dec, int time) {
    int dec_bit = 0;
    int loop_counter = 0;
    if (get_decimal_bit(*x2_dec, 95) == 0) { // условия
        for (int i = 95; i >= 0 && time != 0; i--) {
            if (i != 0) {
                dec_bit = get_decimal_bit(*x2_dec, i - 1);
            }
            if (i == 0) {
                set_decimal_bit(x2_dec, 0, 0, 0);
            } else {
                set_decimal_bit(x2_dec, i / 32, i, dec_bit);
            }
            if (i == 0 && time > 0) {
                i = 95;
                time--;
            }
        }
    }
}
