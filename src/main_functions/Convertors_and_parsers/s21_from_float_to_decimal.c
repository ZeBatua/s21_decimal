#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  if (dst) {
    int scale = 0;
    int binary_exp = getBinaryExp(src);
    int src_sign = !(src >= 0);
    double D_src = (double)src;
    init_decimal(dst);
    if (binary_exp > 95 || binary_exp < -94 || isinf(src) || isnan(src)) {
      error = 1;
    } else {
      for (; !(int)(D_src / 1E7); D_src *= 10) scale += 1;
      D_src =(float)D_src;
      while (fmod(D_src, 10.0) == 0 && scale > 0) {
        D_src /= 10;
        scale--;
        printf("KKK\n");
      }
      if (scale <= 28 && binary_exp + 1 > -95 && binary_exp + 1 <= 95) {
        src = D_src;
        unsigned int fbits = *((unsigned int *)&src);
        binary_exp = getBinaryExp(src) - 1;
        printf("\n\nbinary_exp = %d\n", binary_exp);
        set_decimal_bit(dst, binary_exp / 32, binary_exp % 32, !!binary_exp);
        if (src != 1) {
          unsigned int Fmask = 0b00000000010000000000000000000000;
          unsigned int mask = 1;
          while (binary_exp > -2) {
            set_decimal_bit(dst, binary_exp / 32, binary_exp % 32, fbits & Fmask);
            mask >>= 1;
            Fmask >>= 1;
            binary_exp -= 1;
            printf("A1\n");
          }
        }
      }
      setScale(scale, dst);
      setSign(dst, src_sign);
    }
  } else {
    error = 1;
  }
  return error;
}
