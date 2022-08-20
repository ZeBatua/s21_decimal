#include "../../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    int first_sign = getSign(value_1);
    int second_sign = getSign(value_2);
    setSign(result, !!(first_sign + second_sign));
    s21_decimal first_dec_mask;
    s21_decimal second_dec_mask;
    init_decimal(&first_dec_mask);
    init_decimal(&second_dec_mask);

    if ((getScale(value_1) + getScale(value_2)) > 28) {
        error++;
    }
    int round = get_first_non_zero_bit(value_1);
    int round2 = get_first_non_zero_bit(value_2);
    if (round > round2) round = round2;
    round = 96 - round + 1;
    int shift_counter = 0;
    for (int i = 0; i < 96 && round != 0; i++, round--) {
        create_mask(value_1, value_2, &first_dec_mask, &second_dec_mask, &shift_counter, i);
        smart_print_binary_decimal(first_dec_mask);
        add_no_equote(first_dec_mask, second_dec_mask, result);
        equate_decimal(*result, &second_dec_mask);
    }
    // equate_decimal(first_dec_mask, &result);
    return error;
}

void create_mask(s21_decimal value_1, s21_decimal value_2, s21_decimal *first_dec_mask, s21_decimal *second_dec_mask, int *shift_counter, int bit) {
    int bit_value = get_decimal_bit(value_2, bit);
    if (bit_value == 1) {
        equate_decimal(value_1, first_dec_mask);
    } else {
        init_decimal(first_dec_mask);
    }
    for (int i = 0; i < *shift_counter; i++) {
        shift_left(first_dec_mask, 1);
    }

    // bit_value = get_decimal_bit(value_2, bit + 1);
    // if (bit_value == 1) {
    //     equate_decimal(value_1, &second_dec_mask);
    // }
    // for (int i = 0; i < shift_counter + 1; i++) {
    //     shift_left(&second_dec_mask, 1);
    // }
    *shift_counter +=1;
}
