#include "../../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  if (dst) {
    if (getScale(src) > 28) error = 1;  //проверка что поступивший децимал ок
    *dst = 0.0;
    for (int i = 0; i < 96; i++) {
      if (get_decimal_bit(src, i)) {
        *dst += pow(2, i);
      }
    }
    if (getSign(src)) *dst *= -1;
    int scale = getScale(src);
    double tmp_dst = *dst;
    for (; scale > 0; tmp_dst /= 10, scale--) {
    }
    *dst = (float)tmp_dst;
  } else {
    error = 1;
  }
  return error;  // когда ошибки?
}
