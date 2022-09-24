#include "../../s21_decimal.h"

void setScale(int scale, s21_decimal *value) {
    if (scale >= 0 && scale <= 28) {
        for (int i = 16; i <= 23; i++) {
            int mask = pow(2, i - 16);
            if (scale & mask) {
                setBit(1, &value->bits[3], i);
            } else {
                setBit(0, &value->bits[3], i);
            }
        }
    } 
}
