#include "../../s21_decimal.h"

void equate_decimal(s21_decimal basic, s21_decimal *decimal) {
  init_decimal(decimal);
  for (int i = 0; i < 4; ++i) {
    decimal->bits[i] = basic.bits[i];
  }
}
