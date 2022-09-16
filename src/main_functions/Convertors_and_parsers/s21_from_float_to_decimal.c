#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int error = 0;
    if (dst) {
        int scale = 0;
        int binary_exp = getBinaryExp(src);
        int src_sign = !(src >= 0);
        if (binary_exp > 95 || binary_exp < -94) {
            error = 1;
        } else {
            int check_for_second_for = 0;
            // printf("float before %.15f\n", src);
            for (; !((int)src); src *= 10.0, scale++) {} // нормализовали 0.000123456789 -> 1,23456789
            // printf("float after 1 %.15f\n", src);
            for (int i = 0; i < 7; scale++, src *= 10.0, i++) {} // 8 знаков 1,23456789 -> 12345678,9 // запринтефь
            // printf("float after 2 %.15f\n", src);
            // round(src);
            // printf("float after round %.15f\n", src);
            binary_exp = getBinaryExp(src);
            unsigned int mask = 0x00400000;
            set_decimal_bit(dst, binary_exp / 32, binary_exp % 32, 1);
            unsigned int fbits = *((unsigned int *)&src);
            binary_exp -= 1;
            for (; mask > 0 && binary_exp >= 0; mask >>= 1, binary_exp--) {
                set_decimal_bit(dst, binary_exp / 32, binary_exp % 32, !!(mask & fbits));
            }
            if (scale > 28) error = 1;
            setScale(scale, dst);
            setSign(dst, src_sign);
        }
    } else {
        error = 1;
    }
    return error;
}




// binary_exp = getBinaryExp(src);
//     // unsigned int mask = 0x00400000;
//     // set_decimal_bit(dst, 0, binary_exp, 1); // устанавливаем 1 из флота, которая не хранится в памяти
//     // int float_bit = 0;
//     // int mantiss_to_decimal = binary_exp - 1;
//     // for (; mantiss_to_decimal >= 0; mantiss_to_decimal--) {
//     //     float_bit = get_float_bit(src, &mask);
//     //     set_decimal_bit(dst, mantiss_to_decimal / 32, mantiss_to_decimal % 32, float_bit);
//     // }
// }


// /*
//     У большого флота берешь отаток череще /10  * 10 start - end  = [0-9]
//     первый раз число умножаешь на 1. потом на 10 на 100 и тд
//     каждый раз складываешь свои числа
//     Реализацию дробной части оставить.
//     Взять 8 знаков дробной части.
//     перевести ее в инт и получить двоичную запись в децимал
//     сдвинуть децимал на 8 (умножить на 10)
//     сложить с дробной частью
// */
