#include "../../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    error = equate_scale(&value_1, &value_2);
    init_decimal(result);
    int dec1_sign = getSign(value_1), dec2_sign = getSign(value_2);
    if (!dec1_sign && !dec2_sign) { // оба положительные
        subtraction_no_sign(value_1, value_2, result);
        if (s21_is_less(value_1, value_2)) {
            setSign(*result, 1);
        }
    } else if (dec1_sign && dec2_sign) { // оба отрицательные 
        subtraction_no_sign(value_1, value_2, result);
        if (s21_is_less(value_1, value_2)) {
            setSign(*result, 1);
        } else {
            setSign(*result, 0);
        }
    } else if (dec1_sign == 0 && dec2_sign == 1) { // v1 = +, v2 = -
        setSign(value_2, 0);
        s21_add(value_1, value_2, result);
    } else if (dec1_sign == 1 && dec2_sign == 0) { // v1 = -, v2 = +
        if (is_less_no_sign(value_1, value_2)) {
            subtraction_no_sign(value_1, value_2, result);
            setSign(*result, 0);
        } else {
            subtraction_no_sign(value_1, value_2, result);
            setSign(*result, 1);         
        }
    }
    return error;
}

void subtraction_no_sign(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int first_dec_bit = 0, second_dec_bit = 0, taken_bit = 0;
    for (int i = 0; i < 96; i++) {
        first_dec_bit = get_decimal_bit(value_1, i);
        second_dec_bit =  get_decimal_bit(value_2, i);
        if (taken_bit == 0) {
            if (first_dec_bit == 1 && second_dec_bit == 0) {
                set_decimal_bit(result, i / 32, i, 1);
            } else if (first_dec_bit == 0 && second_dec_bit == 1) {
                set_decimal_bit(result, i / 32, i, 1);
                taken_bit = 1;
            } else if (first_dec_bit == 0 && second_dec_bit == 0) {
                set_decimal_bit(result, i / 32, i, 0);
            } else if (first_dec_bit == 1 && second_dec_bit == 1) {
                set_decimal_bit(result, i / 32, i, 0);
            }
        } else if (first_dec_bit == 1 && second_dec_bit == 0) {
            set_decimal_bit(result, i / 32, i, 0);
            taken_bit = 0;
        } else if (first_dec_bit == 0 && second_dec_bit == 1) {
            set_decimal_bit(result, i / 32, i, 0);
            taken_bit = 1;
        } else if (first_dec_bit == 0 && second_dec_bit == 0) {
            set_decimal_bit(result, i / 32, i, 1);
            taken_bit = 1;
        } else if (first_dec_bit == 1 && second_dec_bit == 1) {
            set_decimal_bit(result, i / 32, i, 1);
            taken_bit = 1;
        }
    }
}
