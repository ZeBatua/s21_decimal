#include "s21_decimal.h"

void shift_right(s21_decimal *decimal, int time) {
    s21_decimal x2_dec;
    init_decimal(&x2_dec);
    equate_decimal(*decimal, &x2_dec);
    int dec_bit = 0;
    for (int i = 0; i < 96 && time != 0; i++) {
        if (i != 95) {
            dec_bit = get_decimal_bit(x2_dec, i + 1);
        }
        if (i == 95) {
            set_decimal_bit(&x2_dec, 2, 95, 0);
        } else {
            set_decimal_bit(&x2_dec, i / 32, i, dec_bit);
        }
        if (i == 95 && time - 1 > 0) {
            i = -1;
            time--;
        }
    }
    equate_decimal(x2_dec, decimal);
    // setScale(getScale(*decimal) + 1, decimal);
}
