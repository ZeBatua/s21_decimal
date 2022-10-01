#include "../../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_extended_decimal ext_value_1, ext_value_2, ext_result, tmp, tmp_val_2;

    int error = 0;
    int dec1_non_zero_extended_bit = 0;
    int dec2_non_zero_extended_bit = 0;
    int step_to_shift = 0, step_to_shift_Scale = 0;
    int width_dec1 = 0, width_dec2 = 0;
    int Sign_for_save = 0, Scale_for_save_dec1 = 0, Scale_for_save_dec2 = 0;
    int mult_x10 = 0, scale_dec1 = 0, scale_dec2 = 0;
    
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
    // equate_ext_scale(&ext_value_1, &ext_value_2);

    printf("ext_value_1\n");
    smart_print_exdec(ext_value_1);
    printf("ext_value_2\n");
    smart_print_exdec(ext_value_2);
    printf("tmp_val2\n");
    smart_print_exdec(tmp_val_2);

    Scale_for_save_dec1 = getScale(value_1);
    Scale_for_save_dec2 = getScale(value_2);
    Sign_for_save = getSign(value_1);
    if (Scale_for_save_dec1 >= 1 || Scale_for_save_dec2 >= 1) {
        if (Scale_for_save_dec1 >= Scale_for_save_dec2) {
            mult_x10 = Scale_for_save_dec1 - Scale_for_save_dec2;
            for (int i = 0; i < mult_x10; i++) {
                multiply_extdec_by_ten(&ext_value_2);
            }
            setExtScale(0, &ext_value_1);
            setExtScale(0, &ext_value_2);
        } else {
            mult_x10 = Scale_for_save_dec2 - Scale_for_save_dec1;
            for (int i = 0; i < mult_x10; i++) {
                multiply_extdec_by_ten(&ext_value_1);
            }
            setExtScale(0, &ext_value_1);
            setExtScale(0, &ext_value_2);
        }
        equate_extdec(ext_value_2, &tmp_val_2);

    }
    printf("\n\n\n\next_value_1 after === scales\n");
    smart_print_exdec(ext_value_1);
    printf("ext_value_2\n");
    smart_print_exdec(ext_value_2);
    printf("tmp_val2\n");
    // smart_print_exdec(tmp_val_2);
    // printf("tmp\n");
    // smart_print_exdec(tmp);
    // printf("ext_result\n");
    // smart_print_exdec(ext_result);
    // setExtScale(max_scale, &tmp_val_2);
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
            shift_left(&ext_value_2, step_to_shift);
            if (is_less_no_sign(ext_value_1, ext_value_2)) shift_right(&ext_value_2, 1);
            printf("ext_value_1 if ext1 > ext2\n");
            smart_print_exdec(ext_value_1);
            printf("ext_value_2 if ext1 > ext2 after shift\n");
            smart_print_exdec(ext_value_2);
            printf("tmp\n");
            smart_print_exdec(tmp);
            if (!is_less_no_sign(ext_value_1, ext_value_2) || is_equal_no_sign(ext_value_1, ext_value_2)) subtraction_no_sign(ext_value_1, ext_value_2, &tmp);
            
        }
        // if (is_less_no_sign(ext_value_1, ext_value_2) ) { // если делимое меньше делителя
        //     step_to_shift = get_first_non_zero_extBit(ext_value_2) - get_first_non_zero_extBit(ext_result);
        //     shift_right(&ext_value_2, step_to_shift);
        //     printf("ext_value_2 -  error\n");
        //     smart_print_exdec(ext_value_2);
        //     subtraction_no_sign(ext_value_1, ext_value_2, &tmp);
        // }
        printf("ext_value_1\n");
        smart_print_exdec(ext_value_1);
        printf("ext_value_2\n");
        smart_print_exdec(ext_value_2);
        printf("tmp_val2\n");
        smart_print_exdec(tmp_val_2);
        printf("tmp\n");
        smart_print_exdec(tmp);
    }
    while (1) { // придумать условие scale и сравнение
        if (!is_less_no_sign(tmp, ext_value_2) || is_equal_no_sign(tmp, ext_value_2)) { // если делимое больше делителя при первом проходе
            step_to_shift = get_first_non_zero_extBit(tmp) - get_first_non_zero_extBit(ext_value_2);
            shift_left(&ext_value_2, step_to_shift);
            if (is_less_no_sign(tmp, ext_value_2)) shift_right(&ext_value_2, 1);
            width_dec2 = get_first_non_zero_extBit(ext_value_2);
            if (!is_less_no_sign(tmp, ext_value_2) || is_equal_no_sign(tmp, ext_value_2)) subtraction_no_sign(tmp, ext_value_2, &tmp);
            if (width_dec2 <= width_dec1) break;
            printf("tmp\n");
            smart_print_exdec(tmp);
            printf("ext_value_2\n");
            smart_print_exdec(ext_value_2);
            
        }
        if (is_less_no_sign(tmp, ext_value_2)) { // если делимое меньше делителя
            step_to_shift = get_first_non_zero_extBit(ext_value_2) - get_first_non_zero_extBit(tmp);
            shift_right(&ext_value_2, step_to_shift);
            if (is_less_no_sign(tmp, ext_value_2)) shift_right(&ext_value_2, 1);
            width_dec2 = get_first_non_zero_extBit(ext_value_2);
            if (width_dec2 < width_dec1) break;
            printf("tmp\n");
            smart_print_exdec(tmp);
            printf("ext_value_2\n");
            smart_print_exdec(ext_value_2);
        }
    }
    error = equate_extdec_to_dec(tmp, result);
    setScale(mult_x10, result);
    if (Sign_for_save) {
        setSign(result, 1);
    } else {
        setSign(result, 0);
    }
    return error;
}