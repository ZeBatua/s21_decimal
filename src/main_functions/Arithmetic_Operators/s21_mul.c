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
    setExtSign(&ext_result, !!(first_sign + second_sign));
    s21_extended_decimal first_dec_mask;
    s21_extended_decimal second_dec_mask;
    init_extended_decimal(&first_dec_mask);
    init_extended_decimal(&second_dec_mask);

    // printf("check decimals\n");
    // smart_print_exdec(ext_value_1);
    // printf("\n");
    // smart_print_exdec(ext_value_2);

    // if (round > round2) round = round2;
    // round = 192 - round + 1;
    // printf("round = %d\n", round);

    int shift_counter = 0;
    // printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < 96; i++) {
        create_mask(ext_value_1, ext_value_2, &first_dec_mask, &second_dec_mask, &shift_counter, i);
        // smart_print_exdec(first_dec_mask);
        // printf("\n");
        add_no_equote(first_dec_mask, second_dec_mask, &ext_result);
        equate_extdec(ext_result, &second_dec_mask);
        // printf("i = %d\n", i);
    }
    // equate_extdec(first_dec_mask, &ext_result);
    // printf("suda\n");
    // printf("scale 1 = %d\n", getExtScale(ext_value_1));
    // printf("scale 2 = %d\n", getExtScale(ext_value_2));

    setExtScale((getExtScale(ext_value_1) + getExtScale(ext_value_2)), &ext_result);
    // printf("summ scale = %d\n", getExtScale(ext_result));
    // smart_print_exdec(ext_result);

    // while (getExtScale(ext_result) > 28) {
    //     division_by_ten(&ext_result);
    // }

    error = equate_extdec_to_dec(ext_result, result);
    // equate_decimal(first_dec_mask, &ext_result);
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
