#include "../s21_decimal.h"

void init_extended_decimal(s21_extended_decimal *decimal) {
  decimal->extBits[0] = 0;
  decimal->extBits[1] = 0;
  decimal->extBits[2] = 0;
  decimal->extBits[3] = 0;
  decimal->extBits[4] = 0;
  decimal->extBits[5] = 0;
  decimal->extBits[6] = 0;
  decimal->extBits[7] = 0;
  decimal->extBits[8] = 0;
  decimal->extBits[9] = 0;
}
