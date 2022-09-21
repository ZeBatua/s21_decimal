#include "../s21_decimal.h"

int setExtScale(int scale, s21_extended_decimal *value) {
  int error = 0;
  if (scale == -1) {
    error = 1;
  } else {
    for (int i = 16; i <= 23; i++) {
      int mask = pow(2, i - 16);
      if (scale & mask) {
        setBit(1, &value->extBits[9], i);
      } else {
        setBit(0, &value->extBits[9], i);
      }
    }
  }
  return error;
}
