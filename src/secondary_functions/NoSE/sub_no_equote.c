#include "../../s21_decimal.h"

int sub_no_equote(s21_extended_decimal value_1, s21_extended_decimal value_2,
                  s21_extended_decimal *result) {
  int error = 0;
  init_extended_decimal(result);
  int dec1_sign = getExtSign(value_1), dec2_sign = getExtSign(value_2);
  if (!dec1_sign && !dec2_sign) {  // оба положительные
    subtraction_no_sign(value_1, value_2, result);
    if (ext_is_less(value_1, value_2)) {
      setExtSign(result, 1);
    }
  } else if (dec1_sign && dec2_sign) {  // оба отрицательные
    subtraction_no_sign(value_1, value_2, result);
    if (ext_is_less(value_1, value_2)) {
      setExtSign(result, 1);
    } else {
      setExtSign(result, 0);
    }
  }
  return error;
}
