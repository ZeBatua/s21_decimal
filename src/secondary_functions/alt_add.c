#include "../s21_decimal.h"

int alt_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    init_decimal(result);
    int first_dec_bit = 0, second_dec_bit = 0;
    int dec1_sign = getSign(value_1), dec2_sign = getSign(value_2);
    int over_bit = 0;
    for (int i = 0; i < 96; i++) {
        first_dec_bit = get_decimal_bit(value_1, i);
        second_dec_bit =  get_decimal_bit(value_2, i);
        if (over_bit == 0) {
            if (first_dec_bit == 1 && second_dec_bit == 0 ||
                first_dec_bit == 0 && second_dec_bit == 1) {
                set_decimal_bit(result, i / 32, i, 1);
            } else if (first_dec_bit == 0 && second_dec_bit == 0) {
                set_decimal_bit(result, i / 32, i, 0);
            } else if (first_dec_bit == 1 && second_dec_bit == 1) {
                set_decimal_bit(result, i / 32, i, 0);
                over_bit = 1;
            }
        } else if (first_dec_bit == 1 && second_dec_bit == 0 ||
            first_dec_bit == 0 && second_dec_bit == 1) {
            set_decimal_bit(result, i / 32, i, 0);
            over_bit = 1;
        } else if (first_dec_bit == 0 && second_dec_bit == 0) {
            set_decimal_bit(result, i / 32, i, 1);
            over_bit = 0;
        } else if (first_dec_bit == 1 && second_dec_bit == 1) {
            set_decimal_bit(result, i / 32, i, 1);
            over_bit = 1;
            if (i == 95) {
                return 1;
            }
        }
    }
}
