#include "../../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (dst) {
    s21_truncate(src, &src);
    *dst = src.bits[0];
    if (getBit(src.bits[3], 31)) {
      *dst *= -1;
    }
  } else {
    error = 1;
  }
  return error;
}
