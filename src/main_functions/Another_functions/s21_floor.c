#include "../../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    int error = 0;
    int sign = getSign(value);
    s21_truncate(value, result);
    if (sign == 1) {
        s21_decimal one;
        init_decimal(&one);
        one.bits[0] = 1;
        s21_add(*result, one, result); // надо нормально чекать переполнение
    }
    return error;
}
