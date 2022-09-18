#include "../../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_extended_decimal ext_value_1, ext_value_2, ext_result;
    s21_extended_decimal temp = {0};
    int error = 0;
    int dec1_non_zero_extended_bit = 0;
    int dec2_non_zero_extended_bit = 0;
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
    smart_print_exdec(ext_result);
    
    dec1_non_zero_extended_bit = get_first_non_zero_extBit(ext_value_1);
    dec2_non_zero_extended_bit = get_first_non_zero_extBit(ext_value_2);
    while (width_dec1 >= width_dec2) { // сравнение ширины делимого и делителя
        printf("%d - width dec1\n", width_dec1);
        printf("%d - width dec2\n", width_dec2);
        if (!is_less_no_sign(ext_value_1, ext_value_2) || is_equal_no_sign(ext_value_1, ext_value_2) || // если делимое больше делителя
            !is_less_no_sign(ext_result, ext_value_2) || is_equal_no_sign(ext_result, ext_value_2)) {
            step_to_shift = dec1_non_zero_extended_bit - dec2_non_zero_extended_bit;
            printf("step_to_shift %d\n", step_to_shift);
            shift_left(&ext_value_2, step_to_shift);
            subtraction_no_sign(ext_value_1, ext_value_2, &ext_value_1);
            printf("\nzdes1\n");
            dec1_non_zero_extended_bit = get_first_non_zero_extBit(ext_result);
            printf("print get_first_non_zero_extBit %d\n", dec1_non_zero_extended_bit);
            dec2_non_zero_extended_bit = get_first_non_zero_extBit(ext_value_2);
            printf("print get_first_non_zero_extBit %d\n", dec2_non_zero_extended_bit);
            smart_print_exdec(ext_result);
            
        }
        if (is_less_no_sign(ext_value_1, ext_value_2) ) { // если делимое меньше делителя
            step_to_shift = get_first_non_zero_extBit(ext_value_2) - get_first_non_zero_extBit(ext_result);
            shift_right(&ext_value_2, step_to_shift);
            subtraction_no_sign(ext_value_1, ext_value_2, &ext_value_1);
            printf("after sub delimoe/delitel\n");
            smart_print_exdec(ext_value_1);
            printf("\nzdes'\n");
        }
        printf("\nzdes' 112121221\n");
        smart_print_exdec(ext_result);
        smart_print_exdec(ext_value_2);
        width_dec1 = get_first_non_zero_extBit(ext_result) - 95;
        width_dec2 = get_first_non_zero_extBit(ext_value_2) - 95;
        printf("%d - width dec1\n", width_dec1);
    }
    error = equate_extdec_to_dec(ext_result, result);
    return error;
}