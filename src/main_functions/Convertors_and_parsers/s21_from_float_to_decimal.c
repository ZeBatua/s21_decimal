#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (dst) {
        int scale = 0;
        int binary_exp = getBinaryExp(src);
        if (binary_exp > 95) {
            return 1;
        } else {
            for (; !((int)src), src *= 10; scale++) { // нормализовали 0.0001234 -> 1,234
                
            }
        }
    } else {
        return 1;
    }


    int Exp = 0;
    Exp = getBinaryExp(src);
}

