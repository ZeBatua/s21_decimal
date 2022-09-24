#include "../../s21_decimal.h"

int is_less_signed(s21_extended_decimal ext_value_1, s21_extended_decimal ext_value_2) {
    int result = 3;
    int first_sign = getExtSign(ext_value_1);
    int second_sign = getExtSign(ext_value_2);
    int bit_v1 = 0;
    int bit_v2 = 0;
    if (first_sign > second_sign) {
        result = 1;
    } else if (first_sign < second_sign) {
        result = 0;
    } else {
        equate_ext_scale(&ext_value_1, &ext_value_2);
        for (int i = 287; i >= 0; i--) {
            bit_v1 = get_extdec_bit(ext_value_1, i);
            bit_v2 = get_extdec_bit(ext_value_2, i);
            if (bit_v1 > bit_v2) {
                result = 0;
                break;
            } else if (bit_v2 > bit_v1) {
                result = 1;
                break;
            }
        }
        if (first_sign && result == 0) {
            result = 1;
        } else if (first_sign && result) {
            result = 0;
        }
        if (result == 3) result = 0;
    }
    return result;
}
