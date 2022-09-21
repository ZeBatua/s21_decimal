#include "../../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    if (s21_is_equal(value_1, value_2)) {
        result = 0;
    } else {
        result = !s21_is_less(value_1, value_2);
    }
    return result;
}
