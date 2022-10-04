#include "../s21_decimal.h"

void equate_extdec(s21_extended_decimal basic,
                   s21_extended_decimal *E_decimal) {
  init_extended_decimal(E_decimal);
  for (int i = 0; i < 10; i++) {
    E_decimal->extBits[i] = basic.extBits[i];
  }
}
