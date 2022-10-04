#include "../s21_decimal.h"

int equate_ext_scale(s21_extended_decimal *first_value,
                     s21_extended_decimal *second_value) {
  int error = 0;
  int first_scale = getExtScale(*first_value);       // 10
  int second_scale = getExtScale(*second_value);     // 11
  int difference = abs(first_scale - second_scale);  // 1

  if (first_scale > second_scale) {
    for (; difference > 0; difference--) {
      multiply_extdec_by_ten(second_value);
    }
  } else {
    for (; difference > 0; difference--) {
      multiply_extdec_by_ten(first_value);
    }
  }

  return error;
}
