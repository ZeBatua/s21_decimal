#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_extended_decimal ext_value_1, ext_value_2;
  equate_dec_to_extdec(value_1, &ext_value_1);
  equate_dec_to_extdec(value_2, &ext_value_2);

  int result = 1;
  int first_sign = getExtSign(ext_value_1);
  int second_sign = getExtSign(ext_value_2);
  int bit_v1 = 0;
  int bit_v2 = 0;
  if (first_sign != second_sign) {
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
        result = 0;
        break;
      }
    }
  }
  return result;
}
