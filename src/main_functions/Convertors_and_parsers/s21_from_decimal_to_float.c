#include "../../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    if (getScale(src) > 28)  return 1;  //проверка что поступивший децимал ок
    *dst = 0.0;
    for (int i = 0; i < 96; i++) {
        if (get_decimal_bit(src, i)) {
            *dst += pow(i, 2);
        }
    }
    if (getSign(src)) *dst *= -1;
    int scale = getScale(src);
    for (; scale > 0; *dst /= 10, scale--) {}
    return 0;  // когда ошибки? 
}
