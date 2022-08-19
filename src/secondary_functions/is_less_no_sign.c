#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    equate_scale(&value_1, &value_2);
    for (int i = 96; i > 0; i--) {
        bit_v1 = get_decimal_bit(value_1, i);
        bit_v2 = get_decimal_bit(value_2, i);
        if (bit_v1 > bit_v2) {
            result = 0;
        } else if (bit_v2 > bit_v1) {
            result = 1;
        }
    }
    return result;
}
