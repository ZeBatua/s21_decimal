#include "../s21_decimal.h"

void setExtScale(int scale, s21_extended_decimal *value) {
    if (scale >= 0 && scale <= 28) {
        for (int i = 16; i <= 23; i++) {
            int mask = pow(2, i - 16);
            if (scale & mask) {
                setBit(1, &value->extBits[9], i);
            } else {
                setBit(0, &value->extBits[9], i);
            }
        }
    } else {
        // printf("trying input invalid scale: %d\n", scale);
    }
}
