#include "../../s21_decimal.h"

int is_less_no_sign(s21_extended_decimal value_1,
                    s21_extended_decimal value_2) {
  int result = 0;
  int bit_v1 = 0;
  int bit_v2 = 0;
  equate_ext_scale(&value_1, &value_2);
  for (int i = 287; i >= 0; i--) {
    bit_v1 = get_extdec_bit(value_1, i);
    bit_v2 = get_extdec_bit(value_2, i);
    if (bit_v1 > bit_v2) {
      result = 0;
      break;
    } else if (bit_v2 > bit_v1) {
      result = 1;
      break;
    }
  }
  return result;
}
