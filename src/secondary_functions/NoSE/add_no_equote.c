#include "../../s21_decimal.h"

int add_no_equote(s21_extended_decimal value_1, s21_extended_decimal value_2, s21_extended_decimal *result) {
    init_extended_decimal(result);
    int error = 0;
    int first_dec_bit = 0, second_dec_bit = 0;
    int dec1_sign = getExtSign(value_1), dec2_sign = getExtSign(value_2);
    int over_bit = 0;
    
    if (dec1_sign == dec2_sign) {
        for (int i = 0; i < 96; i++) {
            first_dec_bit = get_extdec_bit(value_1, i);
            second_dec_bit =  get_extdec_bit(value_2, i);
            if (over_bit == 0) {
                if (first_dec_bit == 1 && second_dec_bit == 0 ||
                    first_dec_bit == 0 && second_dec_bit == 1) {
                    set_extdec_bit(result, i / 32, i, 1);
                } else if (first_dec_bit == 0 && second_dec_bit == 0) {
                    set_extdec_bit(result, i / 32, i, 0);
                } else if (first_dec_bit == 1 && second_dec_bit == 1) {
                    set_extdec_bit(result, i / 32, i, 0);
                    over_bit = 1;
                }
            } else if (first_dec_bit == 1 && second_dec_bit == 0 ||
                first_dec_bit == 0 && second_dec_bit == 1) {
                set_extdec_bit(result, i / 32, i, 0);
                over_bit = 1;
            } else if (first_dec_bit == 0 && second_dec_bit == 0) {
                set_extdec_bit(result, i / 32, i, 1);
                over_bit = 0;
            } else if (first_dec_bit == 1 && second_dec_bit == 1) {
                set_extdec_bit(result, i / 32, i, 1);
                over_bit = 1;
                if (i == 95) {
                    return 1;
                }
            }
        }
        setExtSign(result, getExtSign(value_1)); // уже исправлял в другом сложении. Исправить!
    } else if (is_equal_no_sign(value_1, value_2)) { // иф для а - а = 0
        init_extended_decimal(result); // если 10 + (-10) то что со скейлом и знаком?
    } else {
        sub_no_equote(value_1, value_2, result);
    }
    return error;
}
