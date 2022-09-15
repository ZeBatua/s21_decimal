#include "../../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    s21_extended_decimal ext_value_1, ext_value_2, ext_result;
    init_extended_decimal(&ext_value_1);
    init_extended_decimal(&ext_value_2);
    init_extended_decimal(&ext_result);

    int first_sign = getExtSign(ext_value_1);
    int second_sign = getExtSign(ext_value_2);
    setExtSign(&ext_result, !!(first_sign + second_sign));
    s21_extended_decimal first_dec_mask;
    s21_extended_decimal second_dec_mask;
    init_extended_decimal(&first_dec_mask);
    init_extended_decimal(&second_dec_mask);

    if ((getExtScale(ext_value_1) + getExtScale(ext_value_2)) > 28) error++;
    int round = get_first_non_zero_extBit(ext_value_1);
    int round2 = get_first_non_zero_extBit(ext_value_2);
    if (round > round2) round = round2;
    round = 96 - round + 1;
    int shift_counter = 0;
    for (int i = 0; i < 96 && round != 0; i++, round--) {
        create_mask(ext_value_1, ext_value_2, &first_dec_mask, &second_dec_mask, &shift_counter, i);
        // smart_print_binary_decimal(first_dec_mask);
        add_no_equote(first_dec_mask, second_dec_mask, &ext_result);
        equate_extdec(ext_result, &second_dec_mask);
    }
    // equate_decimal(first_dec_mask, &ext_result);
    return error;
}

void create_mask(s21_extended_decimal ext_value_1, s21_extended_decimal ext_value_2, s21_extended_decimal *first_dec_mask, s21_extended_decimal *second_dec_mask, int *shift_counter, int bit) {
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
