#include "../s21_decimal.h"

int ext_is_less(s21_extended_decimal value_1, s21_extended_decimal value_2) {
    int result = 0;
    int first_sign = getExtSign(value_1);
    int second_sign = getExtSign(value_2);
    int bit_v1 = 0;
    int bit_v2 = 0;
    if (first_sign > second_sign) {
        result = 1;
    } else if (first_sign < second_sign) {
        result = 0;
    } else {
        equate_ext_scale(&value_1, &value_2);
        for (int i = 287; i >= 0; i--) {
            bit_v1 = get_extdec_bit(value_1, i);
            bit_v2 = get_extdec_bit(value_2, i);
            if (bit_v1 > bit_v2) {
                result = 0;
                break;
            } else if (bit_v2 > bit_v1) {
                result = 1;
                break;
            }
            if (first_sign && result) {
                result = 0;
            }
        }
    }
    return result;
}
