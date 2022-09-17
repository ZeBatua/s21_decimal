#include "../../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_extended_decimal ext_value_1, ext_value_2, ext_result;
    int error = 0;
    int first_extended_bit = 0;
    int second_extended_bit = 0;
    int step_to_shift = 0;
    int width_dec1 = 0, width_dec2 = 0;
    
    init_extended_decimal(&ext_value_1);
    init_extended_decimal(&ext_value_2);
    init_extended_decimal(&ext_result);
    init_decimal(result);
    equate_dec_to_extdec(value_1, &ext_value_1);
    equate_dec_to_extdec(value_2, &ext_value_2);
    equate_dec_to_extdec(*result, &ext_result);
    equate_ext_scale(&ext_value_1, &ext_value_2);
    // int dec1_sign = getExtSign(value_1), dec2_sign = getExtSign(value_2);

    first_extended_bit = get_first_non_zero_extBit(ext_value_1);
    second_extended_bit = get_first_non_zero_extBit(ext_value_2);
    
    while (width_dec1 >= width_dec2) {
        width_dec1 = get_first_non_zero_extBit(ext_result);
        width_dec2 = get_first_non_zero_extBit(ext_value_2);
        if (first_extended_bit == second_extended_bit) {
            subtraction_no_sign(ext_value_1, ext_value_2, &ext_result);
            first_extended_bit = get_first_non_zero_extBit(ext_result);
            // continue;
            printf("\nzdes'\n\nzdes'\n\nzdes'\n\nzdes'\n\nzdes'\n\nzdes'\n\nzdes'\n");
        step_to_shift = first_extended_bit - second_extended_bit;
        // smart_print_exdec(ext_value_2);
        shift_left(&ext_value_2, step_to_shift);
        } else if (is_less_no_sign(ext_value_1, ext_value_2)) {
            shift_right(&ext_value_2, 1);
            subtraction_no_sign(ext_value_1, ext_value_2, &ext_result);
            printf("after sub delimoe/delitel\n");
            smart_print_exdec(ext_result);
            printf("\nzdes'\n");
        }
        printf("\nzdes' 112121221\n");
        subtraction_no_sign(ext_value_1, ext_value_2, &ext_result);
        smart_print_exdec(ext_value_2);
    
    }


    error = equate_extdec_to_dec(ext_result, result);
    return error;
}