#include "s21_decimal.h"

void equate_scale(s21_decimal *first_value, s21_decimal *second_value) {
    int first_scale = getScale(*first_value);
    int second_scale = getScale(*second_value);
    int difference = abs(first_scale - second_scale);
    for (int i = 0; i < difference; i++) {
        if (first_scale < second_scale) {
            multiply_by_ten(first_value);
        } else {
            multiply_by_ten(second_value);
        }
    }
}