#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int error = 0;
    if (dst) {
        int scale = 0;
        int binary_exp = getBinaryExp(src);
        int src_sign = !(src >= 0);
        if (binary_exp > 95 || binary_exp < -94) {
            return 1;
        } else {
            s21_extended_decimal ext_result;
            init_extended_decimal(&ext_result);
            float FractionalPart = 0.0;
            float IntengerPart = 0.0;

            FractionalPart = modff(src, &IntengerPart); // modff возвращает дробную часть float, а во второй аргумент помещает целую часть

            SetFractionalPart(FractionalPart, &ext_result);
            SetIntengerPart(IntengerPart, &ext_result);

            error = equate_extdec_to_dec(ext_result, dst);

            if (scale > 28) return 1;
            setScale(scale, dst);
            setSign(dst, src_sign);
        }
    } else {
        return 1;
    }
}

s21_decimal SetFractionalPart(float src, s21_extended_decimal *DecimalFractionalPart) { // если дробной части нет надо возвращать нал наверное
    src /= 100000000.0;
    float get_eight_numbers = 0.0;
    modff(src, &get_eight_numbers);
    int IntFractionalPart = get_eight_numbers;
    DecimalFractionalPart->extBits[0] = IntFractionalPart;



    // int check_for_second_for = 0;
    // printf("float before %.15f\n", src);
    // for (; !((int)src); src *= 10.0, scale++, check_for_second_for = 1) {} // нормализовали 0.000123456789 -> 1,23456789
    // printf("float after 1 %.15f\n", src);
    // for (int i = 0; (i < 7) && (check_for_second_for == 1); scale++, src *= 10, i++) {} // 8 знаков 1,23456789 -> 12345678,9 // запринтефь
    // printf("float after 2 %.15f\n", src);

    // round(src); // это вверх а мне надо обычное
    // printf("float after round %.15f\n", src);


    // // binary_exp = getBinaryExp(src);
    // unsigned int mask = 0x00400000;
    // set_decimal_bit(dst, 0, binary_exp, 1); // устанавливаем 1 из флота, которая не хранится в памяти
    // int float_bit = 0;
    // int mantiss_to_decimal = binary_exp - 1;
    // for (; mantiss_to_decimal >= 0; mantiss_to_decimal--) {
    //     float_bit = get_float_bit(src, &mask);
    //     set_decimal_bit(dst, mantiss_to_decimal / 32, mantiss_to_decimal % 32, float_bit);
    // }
}


/*
    У большого флота берешь отаток череще /10  * 10 start - end  = [0-9]
    первый раз число умножаешь на 1. потом на 10 на 100 и тд
    каждый раз складываешь свои числа
    Реализацию дробной части оставить.
    Взять 8 знаков дробной части.
    перевести ее в инт и получить двоичную запись в децимал
    сдвинуть децимал на 8 (умножить на 10)
    сложить с дробной частью
*/
