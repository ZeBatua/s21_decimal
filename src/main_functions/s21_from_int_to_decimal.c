#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int error = 0;
    if (dst) {
        init_decimal(dst);
        if (src < 0) {
            setBit(1, &dst->bits[3], 31);
            src *= -1;
        }
        dst->bits[0] = src;
    } else {
        error = 1;
    }
    return error;
}
