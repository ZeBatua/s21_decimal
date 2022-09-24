#include "../../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result) {
  int error = 0;
  s21_extended_decimal ext_value_1, ext_value_2, ext_result;
  init_extended_decimal(&ext_value_1);
  init_extended_decimal(&ext_value_2);
  init_extended_decimal(&ext_result);
  equate_dec_to_extdec(value_1, &ext_value_1);
  equate_dec_to_extdec(value_2, &ext_value_2);
  init_decimal(result);
  int first_extdec_bit = 0, second_extdec_bit = 0;
  int dec1_sign = getExtSign(ext_value_1), dec2_sign = getExtSign(ext_value_2);
  int over_bit = 0;
  error = equate_ext_scale(&ext_value_1, &ext_value_2);

  if (dec1_sign == dec2_sign) {
    for (int i = 0; i < 288; i++) {
      first_extdec_bit = get_extdec_bit(ext_value_1, i);
      second_extdec_bit = get_extdec_bit(ext_value_2, i);
      if (over_bit == 0) {
        if ((first_extdec_bit == 1 && second_extdec_bit == 0) ||
            (first_extdec_bit == 0 && second_extdec_bit == 1)) {
          set_extdec_bit(&ext_result, i / 32, i, 1);
        } else if (first_extdec_bit == 0 && second_extdec_bit == 0) {
          set_extdec_bit(&ext_result, i / 32, i, 0);
        } else if (first_extdec_bit == 1 && second_extdec_bit == 1) {
          set_extdec_bit(&ext_result, i / 32, i, 0);
          over_bit = 1;
        }
      } else if ((first_extdec_bit == 1 && second_extdec_bit == 0) ||
                 (first_extdec_bit == 0 && second_extdec_bit == 1)) {
        set_extdec_bit(&ext_result, i / 32, i, 0);
        over_bit = 1;
      } else if (first_extdec_bit == 0 && second_extdec_bit == 0) {
        set_extdec_bit(&ext_result, i / 32, i, 1);
        over_bit = 0;
      } else if (first_extdec_bit == 1 && second_extdec_bit == 1) {
        set_extdec_bit(&ext_result, i / 32, i, 1);
        over_bit = 1;
      }
    }
    if (error == 1 && dec1_sign == 1) error = 2;
    setExtSign(&ext_result, (dec1_sign > 0));
    setExtScale(getExtScale(ext_value_1), &ext_result);
  } else if (is_equal_no_sign(
                 ext_value_1,
                 ext_value_2)) {
    init_decimal(result);
  } else {
    if (is_less_no_sign(ext_value_1, ext_value_2) &&
        getExtSign(ext_value_2) == 1) {
      setSign(&value_2, 0);
      s21_sub(value_2, value_1, result);
      setSign(result, 1);
    } else if (is_less_no_sign(ext_value_1, ext_value_2) &&
               !getExtSign(ext_value_2)) {
      setSign(&value_1, 0);
      s21_sub(value_2, value_1, result);
      setSign(result, 0);
    } else if (!is_less_no_sign(ext_value_1, ext_value_2) &&
               getExtSign(ext_value_1)) {
      setSign(&value_1, 0);
      s21_sub(value_1, value_2, result);
      setSign(result, 1);
    } else if (!is_less_no_sign(ext_value_1, ext_value_2) &&
               !getExtSign(ext_value_1)) {
      setSign(&value_2, 0);
      s21_sub(value_1, value_2, result);
      setSign(result, 0);
    }
    equate_dec_to_extdec(*result, &ext_result);
  }
  
  error = equate_extdec_to_dec(
      ext_result, result);
  return error;
}
