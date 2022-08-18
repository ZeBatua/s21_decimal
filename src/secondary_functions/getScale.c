#include "../s21_decimal.h"

int getScale(s21_decimal value) {
    int scale = 0;
    for (int i = 7; i >= 0; --i) {
        if (getBit(value.bits[3], 16 + i) == 1) {
            scale += pow(2, i);
        }
    }
    return scale;
}
