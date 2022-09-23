#include "../../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_extended_decimal ext_value_1, ext_value_2, ext_result, tmp, tmp_val_2;

    int error = 0;
    int dec1_non_zero_extended_bit = 0;
    int dec2_non_zero_extended_bit = 0;
    int step_to_shift = 0;
    int width_dec1 = 0, width_dec2 = 0;
    
    init_extended_decimal(&ext_value_1);
    init_extended_decimal(&ext_value_2);
    init_extended_decimal(&ext_result);
    init_extended_decimal(&tmp);
    init_extended_decimal(&tmp_val_2);
    init_decimal(result);
    equate_dec_to_extdec(value_1, &ext_value_1);
    equate_dec_to_extdec(value_2, &ext_value_2);
    equate_dec_to_extdec(value_2, &tmp_val_2);
    equate_dec_to_extdec(*result, &ext_result);
    equate_dec_to_extdec(*result, &tmp);
    
    equate_ext_scale(&ext_value_1, &ext_value_2);
    width_dec1 = get_first_non_zero_extBit(tmp_val_2);

    if (is_less_no_sign(ext_value_1, ext_value_2) && is_equal_no_sign(tmp, ext_result)) { // если делимое меньше делителя - делимое является остатком
        equate_extdec(ext_value_1, &tmp);
    } else if (is_equal_no_sign(tmp, ext_result)) {
        if (is_equal_no_sign(ext_value_1, ext_value_2)) {
            init_decimal(result);
        }
        if (!is_less_no_sign(ext_value_1, ext_value_2)) { // если делимое больше делителя при первом проходе
            printf("start dec %d\nstart dec2 %d\n", get_first_non_zero_extBit(ext_value_1), get_first_non_zero_extBit(ext_value_2));
            step_to_shift = get_first_non_zero_extBit(ext_value_1) - get_first_non_zero_extBit(ext_value_2);
            // printf("step_to_shift %d\n", step_to_shift);
            shift_left(&ext_value_2, step_to_shift);
            if (is_less_no_sign(ext_value_1, ext_value_2)) shift_right(&ext_value_2, 1);
            if (!is_less_no_sign(ext_value_1, ext_value_2) || is_equal_no_sign(ext_value_1, ext_value_2)) subtraction_no_sign(ext_value_1, ext_value_2, &tmp);
            // printf("\nzdes1\n");
            // printf("print tmp decimal if \n");
            
        }
        if (is_less_no_sign(ext_value_1, ext_value_2) ) { // если делимое меньше делителя
            step_to_shift = get_first_non_zero_extBit(ext_value_2) - get_first_non_zero_extBit(ext_result);
            shift_right(&ext_value_2, step_to_shift);
            subtraction_no_sign(ext_value_1, ext_value_2, &tmp);
            // printf("after sub delimoe/delitel\n");
            // smart_print_exdec(tmp);
            // printf("\nzdes'\n");
        }
    }
        // printf("After first entrie!!!!!!!!\n");
        // smart_print_exdec(ext_value_1);
        // smart_print_exdec(ext_value_2);
        // smart_print_exdec(tmp);
        // smart_print_exdec(tmp_val_2);
    while (1) { // придумать условие
        if (!is_less_no_sign(tmp, ext_value_2) || is_equal_no_sign(tmp, ext_value_2)) { // если делимое больше делителя при первом проходе
            step_to_shift = get_first_non_zero_extBit(tmp) - get_first_non_zero_extBit(ext_value_2);
            shift_left(&ext_value_2, step_to_shift);
            if (is_less_no_sign(tmp, ext_value_2)) shift_right(&ext_value_2, 1);
            width_dec2 = get_first_non_zero_extBit(ext_value_2);
            if (width_dec2 <= width_dec1) break;
            if (!is_less_no_sign(tmp, ext_value_2) || is_equal_no_sign(tmp, ext_value_2)) subtraction_no_sign(tmp, ext_value_2, &tmp);
            // printf("if tmp > ext_value2\nprint ext_value_2 decimal\nprint tmp decimal\n");
            // smart_print_exdec(tmp);
            // smart_print_exdec(ext_value_2);
            
        }
        if (is_less_no_sign(tmp, ext_value_2)) { // если делимое меньше делителя
            step_to_shift = get_first_non_zero_extBit(ext_value_2) - get_first_non_zero_extBit(tmp);
            shift_right(&ext_value_2, step_to_shift);
            if (is_less_no_sign(tmp, ext_value_2)) shift_right(&ext_value_2, 1);
            // printf("before sub delimoe/delitel step to shift rigth %d\n", step_to_shift);
            // printf("print tmp decimal\nprint ext_value_2 decimal\n");
            // smart_print_exdec(tmp);
            // smart_print_exdec(ext_value_2);
            
            width_dec2 = get_first_non_zero_extBit(ext_value_2);
            if (width_dec2 < width_dec1) break;
            subtraction_no_sign(tmp, ext_value_2, &tmp);
            // smart_print_exdec(tmp);
            // smart_print_exdec(ext_value_2);
            
            // printf("w_dec1 - %d, w_dec2 - %d\n", width_dec1, width_dec2);
        }
    }
    error = equate_extdec_to_dec(tmp, result);
    
    return error;
}