#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {

    if (dst) { // нужна нормальная проверка
        int scale = 0;
        int binary_exp = getBinaryExp(src);
        int src_sign = !(src >= 0);
        if (binary_exp > 95 || binary_exp < -94) {
            return 1;
        } else {
            int check_for_second_for = 0;
            for (; !((int)src); src *= 10, scale++, check_for_second_for = 1) {} // нормализовали 0.000123456789 -> 1,23456789
            printf("check = %d\n", check_for_second_for);
            for (int i = 0; (i < 7) && (check_for_second_for == 1); scale++, src *= 10, i++) {} // 8 знаков 1,23456789 -> 12345678,9 // запринтефь
            ceil(src); // это вверх а мне надо обычное
            binary_exp = getBinaryExp(src);
            unsigned int mask = 0x400000;
            set_decimal_bit(dst, 0, binary_exp, 1); // устанавливаем 1 из флота, которая не хранится в памяти
            int float_bit = 0;
            int mantiss_to_decimal = binary_exp - 1;
            for (; mantiss_to_decimal >= 0; mantiss_to_decimal--) {
                float_bit = get_float_bit(src, &mask);
                set_decimal_bit(dst, binary_exp / 32, binary_exp % 32, float_bit);
            }
            if (scale > 28) return 1;
            setScale(scale, dst);
            setSign(dst, src_sign);
        }
    } else {
        return 1;
    }
}
