#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int scale = 0, error = 0;
    scale = getScale(value);
    for (int i = 0; i < scale; i++) {
        // division_scale(&value);
    }
    return error;
}
