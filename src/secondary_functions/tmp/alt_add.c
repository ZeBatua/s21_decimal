#include "../../s21_decimal.h"

int alt_add(s21_extended_decimal value_1, s21_extended_decimal value_2, s21_extended_decimal *result) {
    init_extended_decimal(result);
    int error = 0;
    int first_dec_bit = 0, second_dec_bit = 0;
    int over_bit = 0;
    for (int i = 0; i < 288; i++) {
        first_dec_bit = get_extdec_bit(value_1, i);
        second_dec_bit =  get_extdec_bit(value_2, i);
        if (over_bit == 0) {
            if ((first_dec_bit == 1 && second_dec_bit == 0) ||
                (first_dec_bit == 0 && second_dec_bit == 1)) {
                set_extdec_bit(result, i / 32, i, 1);
            } else if (first_dec_bit == 0 && second_dec_bit == 0) {
                set_extdec_bit(result, i / 32, i, 0);
            } else if (first_dec_bit == 1 && second_dec_bit == 1) {
                set_extdec_bit(result, i / 32, i, 0);
                over_bit = 1;
                if (i == 287) {
                    error = 1;
                }
            }
        } else if ((first_dec_bit == 1 && second_dec_bit == 0) ||
            (first_dec_bit == 0 && second_dec_bit == 1)) {
            set_extdec_bit(result, i / 32, i, 0);
            over_bit = 1;
            if (i == 287) {
                error = 1;
            }
        } else if (first_dec_bit == 0 && second_dec_bit == 0) {
            set_extdec_bit(result, i / 32, i, 1);
            over_bit = 0;
        } else if (first_dec_bit == 1 && second_dec_bit == 1) {
            set_extdec_bit(result, i / 32, i, 1);
            over_bit = 1;
            if (i == 287) {
                error = 1;
            }
        }
    }
    return error;
}
