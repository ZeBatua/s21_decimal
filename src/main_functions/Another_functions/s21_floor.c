#include "../../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if(!getSign(value)) { // 1.7 -> 1; 1,23 -> 1; 909,1 -> 909
        s21_truncate(value, result);    
    } else { // -1.7 -> -2; -4 -> -4;
        s21_decimal buf_value;
        init_decimal(&buf_value);
        equate_decimal(value, &buf_value);
        s21_truncate(value, &value);    
        if (s21_is_not_equal(value, buf_value)) {
            s21_decimal one;
            init_decimal(&one);
            one.bits[0] = 1;
            setSign(&one, 1);
            s21_add(value, one, result);
            smart_print_binary_decimal(*result);
        } else {
            equate_decimal(value, result);
        }
    }
    return error;
}
