#include "../s21_decimal.h"

void setExtSign(s21_extended_decimal *value, int sign) {
  int mask = 1;
  if (get_extdec_bit(*value, 319) != sign) {
    mask = mask << 31;
    value->extBits[9] ^= mask;
  }
}
