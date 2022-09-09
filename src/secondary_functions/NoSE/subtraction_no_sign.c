#include "../../s21_decimal.h"

void subtraction_no_sign(s21_extended_decimal value_1, s21_extended_decimal value_2, s21_extended_decimal *result) {
    int first_dec_bit = 0, second_dec_bit = 0, taken_bit = 0;
    for (int i = 0; i < 289; i++) {
        first_dec_bit = get_extdec_bit(value_1, i);
        second_dec_bit =  get_extdec_bit(value_2, i);
        if (taken_bit == 0) {
            if (first_dec_bit == 1 && second_dec_bit == 0) {
                set_extdec_bit(result, i / 32, i, 1);
            } else if (first_dec_bit == 0 && second_dec_bit == 1) {
                set_extdec_bit(result, i / 32, i, 1);
                taken_bit = 1;
            } else if (first_dec_bit == 0 && second_dec_bit == 0) {
                set_extdec_bit(result, i / 32, i, 0);
            } else if (first_dec_bit == 1 && second_dec_bit == 1) {
                set_extdec_bit(result, i / 32, i, 0);
            }
        } else if (first_dec_bit == 1 && second_dec_bit == 0) {
            set_extdec_bit(result, i / 32, i, 0);
            taken_bit = 0;
        } else if (first_dec_bit == 0 && second_dec_bit == 1) {
            set_extdec_bit(result, i / 32, i, 0);
            taken_bit = 1;
        } else if (first_dec_bit == 0 && second_dec_bit == 0) {
            set_extdec_bit(result, i / 32, i, 1);
            taken_bit = 1;
        } else if (first_dec_bit == 1 && second_dec_bit == 1) {
            set_extdec_bit(result, i / 32, i, 1);
            taken_bit = 1;
        }
    }
    setExtScale(getExtScale(value_1), result);
}
