#include "../../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    s21_extended_decimal ext_value_1, ext_value_2, ext_result;
    init_extended_decimal(&ext_value_1);
    init_extended_decimal(&ext_value_2);
    init_extended_decimal(&ext_result);

    equate_dec_to_extdec(value_1, &ext_value_1);
    equate_dec_to_extdec(value_2, &ext_value_2);
    equate_dec_to_extdec(*result, &ext_result);

    int first_sign = getExtSign(ext_value_1);
    int second_sign = getExtSign(ext_value_2);
    s21_extended_decimal first_dec_mask;
    s21_extended_decimal second_dec_mask;
    init_extended_decimal(&first_dec_mask);
    init_extended_decimal(&second_dec_mask);

    int shift_counter = 0;
    for (int i = 0; i < 96; i++) {
        create_mask(ext_value_1, ext_value_2, &first_dec_mask, &second_dec_mask, &shift_counter, i);

        add_no_equote(first_dec_mask, second_dec_mask, &ext_result);
        equate_extdec(ext_result, &second_dec_mask);
    }
    setExtScale((getExtScale(ext_value_1) + getExtScale(ext_value_2)), &ext_result);
    if (first_sign && second_sign) {
        setExtSign(&ext_result, 0);
    } else if (first_sign || second_sign) {
        setExtSign(&ext_result, 1);
    }
    error = equate_extdec_to_dec(ext_result, result);

    return error;
}

void create_mask(s21_extended_decimal ext_value_1, s21_extended_decimal ext_value_2,
                 s21_extended_decimal *first_dec_mask, s21_extended_decimal *second_dec_mask,
                 int *shift_counter, int bit) {
    int bit_value = get_extdec_bit(ext_value_2, bit);
    if (bit_value == 1) {
        equate_extdec(ext_value_1, first_dec_mask);
    } else {
        init_extended_decimal(first_dec_mask);
    }
    for (int i = 0; i < *shift_counter; i++) {
        shift_left(first_dec_mask, 1);
    }
    *shift_counter +=1;
}
