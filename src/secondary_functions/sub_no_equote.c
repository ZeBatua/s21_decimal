#include "../s21_decimal.h"

int sub_no_equote(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    init_decimal(result);
    int dec1_sign = getSign(value_1), dec2_sign = getSign(value_2);
    if (!dec1_sign && !dec2_sign) { // оба положительные
        subtraction_no_sign(value_1, value_2, result);
        if (s21_is_less(value_1, value_2)) {
            setSign(result, 1);
        }
    } else if (dec1_sign && dec2_sign) { // оба отрицательные 
        subtraction_no_sign(value_1, value_2, result);
        if (s21_is_less(value_1, value_2)) {
            setSign(result, 1);
        } else {
            setSign(result, 0);
        }
    } else if (dec1_sign == 0 && dec2_sign == 1) { // v1 = +, v2 = -
        setSign(&value_2, 0);
        add_no_equote(value_1, value_2, result);
    } else if (dec1_sign == 1 && dec2_sign == 0) { // v1 = -, v2 = +
        if (is_less_no_sign(value_1, value_2)) {
            subtraction_no_sign(value_1, value_2, result);
            setSign(result, 0);
        } else {
            subtraction_no_sign(value_1, value_2, result);
            setSign(result, 1);         
        }
    }
    return error;
}
