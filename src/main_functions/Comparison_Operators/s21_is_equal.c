#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    int first_sign = getSign(value_1);
    int second_sign = getSign(value_2);
    int bit_v1 = 0;
    int bit_v2 = 0;
    if (first_sign != second_sign) {
        result = 0;
    } else {
        equate_scale(&value_1, &value_2);
        for (int i = 96; i > 0; i--) {
            bit_v1 = get_decimal_bit(value_1, i);
            bit_v2 = get_decimal_bit(value_2, i);
            if (bit_v1 > bit_v2) {
                result = 0;
                break;
            } else if (bit_v2 > bit_v1) {
                result = 0;
                break;
            }
        }
        if (result == 0) result = 1;
    }
    return result;
}

