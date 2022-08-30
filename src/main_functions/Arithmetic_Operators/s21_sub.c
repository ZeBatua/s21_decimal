#include "../../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_extended_decimal ext_value_1, ext_value_2, ext_result;
    equate_dec_to_extdec(value_1, &ext_value_1);
    equate_dec_to_extdec(value_2, &ext_value_2);
    equate_dec_to_extdec(*result, &ext_result);
    int error = 0;
    error = equate_ext_scale(&ext_value_1, &ext_value_2);
    int dec1_sign = getExtSign(ext_value_1), dec2_sign = getExtSign(ext_value_2);
    if (!dec1_sign && !dec2_sign) { // оба положительные
        subtraction_no_sign(ext_value_1, ext_value_2, &ext_result);
        if (ext_is_less(ext_value_1, ext_value_2)) {
            setExtSign(&ext_result, 1);
        }
    } else if (dec1_sign && dec2_sign) { // оба отрицательные 
        subtraction_no_sign(ext_value_1, ext_value_2, &ext_result);
        if (ext_is_less(ext_value_1, ext_value_2)) {
            setExtSign(&ext_result, 1);
        } else {
            setExtSign(&ext_result, 0);
        }
    } else if (dec1_sign == 0 && dec2_sign == 1) { // v1 = +, v2 = -
        setExtSign(&ext_value_2, 0);
        s21_add(value_1, value_2, result);
    } else if (dec1_sign == 1 && dec2_sign == 0) { // v1 = -, v2 = +
        if (is_less_no_sign(ext_value_1, ext_value_2)) {
            subtraction_no_sign(ext_value_1, ext_value_2, &ext_result);
            setExtSign(&ext_result, 0);
        } else {
            subtraction_no_sign(ext_value_1, ext_value_2, &ext_result);
            setExtSign(&ext_result, 1);         
        }
    }
    return error;
}
