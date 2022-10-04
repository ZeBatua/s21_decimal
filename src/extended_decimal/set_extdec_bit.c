#include "../s21_decimal.h"

void set_extdec_bit(s21_extended_decimal *E_decimal, int bait, int position,
                    int value) {  // мб чар
  if (value == 1) {
    if (get_extdec_bit(*E_decimal, position) == 0) {
      int mask = 1;
      mask = mask << position;
      E_decimal->extBits[bait] |= mask;
    }
  } else if (value == 0) {
    if (get_extdec_bit(*E_decimal, position) == 1) {
      int mask = 1;
      mask = mask << position;
      mask = ~mask;
      E_decimal->extBits[bait] &= mask;
    }
  }
}
