#include "../../s21_decimal.h"

void shift_left(s21_extended_decimal *x2_dec, int time) {
  int dec_bit = 0;
  for (int i = 287; i >= 0 && time != 0; i--) {
    if (i != 0) {
      dec_bit = get_extdec_bit(*x2_dec, i - 1);
    }
    if (i == 0) {
      set_extdec_bit(x2_dec, 0, 0, 0);
    } else {
      set_extdec_bit(x2_dec, i / 32, i, dec_bit);
    }
    if (i == 0 && time > 0) {
      i = 287;  // 288 потому что фор сделает -1 288 -> 287, но это не точно.
                // Надо тестить.
      time--;
    }
  }
}
