#include "../s21_decimal.h"

void multiply_extdec_by_ten(s21_extended_decimal *E_decimal) {
  s21_extended_decimal x2_dec, x8_dec;
  init_extended_decimal(&x2_dec);
  init_extended_decimal(&x8_dec);
  equate_extdec(*E_decimal, &x2_dec);
  equate_extdec(*E_decimal, &x8_dec);
  int save_scale = getExtScale(*E_decimal);
  int save_sign = getExtSign(*E_decimal);
  shift_left(&x2_dec, 1);
  shift_left(&x8_dec, 3);
  s21_extended_decimal result;
  init_extended_decimal(&result);
  add_no_equote(x2_dec, x8_dec,
                &result);
  equate_extdec(result, E_decimal);
  setExtScale(save_scale, E_decimal);
  setExtSign(E_decimal, save_sign);
  setExtScale(getExtScale(*E_decimal) + 1, E_decimal);
}
