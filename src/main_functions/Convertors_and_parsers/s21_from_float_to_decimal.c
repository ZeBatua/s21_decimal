#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (dst) {
        int scale = 0;
        int binary_exp = getBinaryExp(src);
        if (binary_exp > 95) {
            return 1;
        } else {
            for (; !((int)src), src *= 10; scale++) {} // нормализовали 0.000123456789 -> 1,23456789
            for (int i = 0; src *= 10, i < 8 ; scale++) {} // 8 знаков 1,23456789 -> 12345678,9
        }
    } else {
        return 1;
    }


    int Exp = 0;
    Exp = getBinaryExp(src);
}

