#include "../../s21_decimal.h"

int sub_no_equote(s21_extended_decimal value_1, s21_extended_decimal value_2, s21_extended_decimal *result) {
    int error = 0;
    init_extended_decimal(result);
    int dec1_sign = getExtSign(value_1), dec2_sign = getExtSign(value_2);
    if (!dec1_sign && !dec2_sign) { // оба положительные
        subtraction_no_sign(value_1, value_2, result);
        if (ext_is_less(value_1, value_2)) {
            setExtSign(result, 1);
        }
    } else if (dec1_sign && dec2_sign) { // оба отрицательные 
        subtraction_no_sign(value_1, value_2, result);
        if (ext_is_less(value_1, value_2)) {
            setExtSign(result, 1);
        } else {
            setExtSign(result, 0);
        }
    } else if (dec1_sign == 0 && dec2_sign == 1) { // v1 = +, v2 = -
        setExtSign(&value_2, 0);
        add_no_equote(value_1, value_2, result);
    } else if (dec1_sign == 1 && dec2_sign == 0) { // v1 = -, v2 = +
        if (is_less_no_sign(value_1, value_2)) {
            subtraction_no_sign(value_1, value_2, result);
            setExtSign(result, 0);
        } else {
            subtraction_no_sign(value_1, value_2, result);
            setExtSign(result, 1);         
        }
    }
    return error;
}
