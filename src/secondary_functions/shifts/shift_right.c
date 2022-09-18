#include "../../s21_decimal.h"

void shift_right(s21_extended_decimal *decimal, int time) {
    s21_extended_decimal x2_dec;
    init_extended_decimal(&x2_dec);
    equate_extdec(*decimal, &x2_dec);
    int dec_bit = 0;
    for (int i = 0; i < 288 && time != 0; i++) {
        if (i != 287) {
            dec_bit = get_extdec_bit(x2_dec, i + 1);
        }
        if (i == 287) {
            set_extdec_bit(&x2_dec, 2, 287, 0);
        } else {
            set_extdec_bit(&x2_dec, i / 32, i, dec_bit);
        }
        if (i == 287 && time - 1 > 0) {
            i = -1;
            time--;
        }
    }
    equate_extdec(x2_dec, decimal);
}
