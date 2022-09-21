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
    // int dec1_sign = getExtSign(value_1), dec2_sign = getExtSign(value_2);
    smart_print_exdec(ext_result);
    
    // dec1_non_zero_extended_bit = get_first_non_zero_extBit(ext_value_1);
    // dec2_non_zero_extended_bit = get_first_non_zero_extBit(ext_value_2);
    
    while (1) { // сравнение ширины делимого и делителя
        // printf("%d - width dec1\n", width_dec1);
        // printf("%d - width dec2\n", width_dec2);
        if (is_less_no_sign(ext_value_1, ext_value_2) && is_equal_no_sign(tmp, ext_result)) { // если делимое меньше делителя - делимое является остатком
            error = equate_extdec_to_dec(ext_value_1, result);
        } else if (is_equal_no_sign(tmp, ext_result)) {
            if (!is_less_no_sign(ext_value_1, ext_value_2) || is_equal_no_sign(ext_value_1, ext_value_2)) { // если делимое больше делителя при первом проходе
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
        printf("After first entrie!!!!!!!!\n");
        smart_print_exdec(ext_value_1);
        smart_print_exdec(ext_value_2);
        smart_print_exdec(tmp);
        smart_print_exdec(tmp_val_2);
        // printf("%d - width dec1\n", width_dec1);
        // printf("%d - width dec2\n", width_dec2);
        while (is_less_no_sign(tmp_val_2, tmp) || width_dec2 <= width_dec1) { // придумать условие
            if (!is_less_no_sign(tmp, ext_value_2) || is_equal_no_sign(tmp, ext_value_2)) { // если делимое больше делителя при первом проходе
                width_dec2 = get_first_non_zero_extBit(tmp) - 95;
                width_dec1 = get_first_non_zero_extBit(tmp_val_2) - 95;
                step_to_shift = get_first_non_zero_extBit(ext_value_1) - get_first_non_zero_extBit(ext_value_2);
                // printf("step_to_shift %d\n", step_to_shift);
                shift_left(&ext_value_2, step_to_shift);
                if (is_less_no_sign(tmp, ext_value_2)) shift_right(&ext_value_2, 1);
                if (!is_less_no_sign(tmp, ext_value_2) || is_equal_no_sign(tmp, ext_value_2)) subtraction_no_sign(tmp, ext_value_2, &tmp);
                // printf("\nzdes1\n");
                // dec1_non_zero_extended_bit = get_first_non_zero_extBit(ext_result);
                // dec2_non_zero_extended_bit = get_first_non_zero_extBit(ext_value_2);
                // printf("print get_first_non_zero_extBit %d\n", dec1_non_zero_extended_bit);
                // printf("print tmp decimal if \n");
                // smart_print_exdec();
                smart_print_exdec(ext_value_2);
                smart_print_exdec(tmp);
            }
            if (is_less_no_sign(tmp, ext_value_2) ) { // если делимое меньше делителя
                step_to_shift = get_first_non_zero_extBit(ext_value_2) - get_first_non_zero_extBit(tmp);
                shift_right(&ext_value_2, step_to_shift);
                subtraction_no_sign(tmp, ext_value_2, &tmp); // структура забивается мусором, нужна функция для временного хранения(?)
                printf("after sub delimoe/delitel\n");
                smart_print_exdec(tmp);
                printf("\nzdes'\n");
            }
            printf("%d - width dec1\n", width_dec1);
            printf("%d - width dec2\n", width_dec2);
            smart_print_exdec(ext_value_2);
            smart_print_exdec(tmp);
        }
        error = equate_extdec_to_dec(tmp, result);
        break;
    }
    
    return error;
}