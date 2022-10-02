#include "../../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_extended_decimal ext_value_1, ext_value_2, ext_result, tmp, tmp_val_2;
    int error = 0, error_nan = 5;
    int step_to_shift = 0;
    int width_dec1 = 0, width_dec2 = 0;
    int Sign_for_save = 0, Scale_for_save_dec1 = 0, Scale_for_save_dec2 = 0;
    int mult_x10 = 0, high_scale = 0;
    
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

    Scale_for_save_dec1 = getScale(value_1);
    Scale_for_save_dec2 = getScale(value_2);
    Sign_for_save = getSign(value_1);
    if (Scale_for_save_dec1 >= 1 || Scale_for_save_dec2 >= 1) {
        if (Scale_for_save_dec1 > Scale_for_save_dec2) {
            high_scale = Scale_for_save_dec1;
            mult_x10 = Scale_for_save_dec1 - Scale_for_save_dec2;
            for (int i = 0; i < mult_x10; i++) {
                multiply_extdec_by_ten(&ext_value_2);
            }
        } else if (Scale_for_save_dec1 < Scale_for_save_dec2) {
            high_scale = Scale_for_save_dec2;
            mult_x10 = Scale_for_save_dec2 - Scale_for_save_dec1;
            for (int i = 0; i < mult_x10; i++) {
                multiply_extdec_by_ten(&ext_value_1);
            }
        } else {
            high_scale = Scale_for_save_dec1;
        }
        equate_extdec(ext_value_2, &tmp_val_2);
    }
    width_dec1 = get_first_non_zero_extBit(tmp_val_2);
    if (is_less_no_sign(ext_value_1, ext_value_2) && is_equal_no_sign(tmp, ext_result)) {
        equate_extdec(ext_value_1, &tmp);
    } else if (is_equal_no_sign(ext_value_2, ext_result)) {
        error_nan = 3;
    } else if (is_equal_no_sign(tmp, ext_result)) {
        if (is_equal_no_sign(ext_value_1, ext_value_2)) {
            init_decimal(result);
        }
        if (!is_less_no_sign(ext_value_1, ext_value_2)) {
            step_to_shift = get_first_non_zero_extBit(ext_value_1) - get_first_non_zero_extBit(ext_value_2);
            shift_left(&ext_value_2, step_to_shift);
            if (is_less_no_sign(ext_value_1, ext_value_2)) shift_right(&ext_value_2, 1);
            if (!is_less_no_sign(ext_value_1, ext_value_2) || is_equal_no_sign(ext_value_1, ext_value_2)) subtraction_no_sign(ext_value_1, ext_value_2, &tmp);
        }
    }
    if (error_nan != 3) {
        while (1) {
            if (!is_less_no_sign(tmp, ext_value_2) || is_equal_no_sign(tmp, ext_value_2)) {
                step_to_shift = get_first_non_zero_extBit(tmp) - get_first_non_zero_extBit(ext_value_2);
                shift_left(&ext_value_2, step_to_shift);
                if (is_less_no_sign(tmp, ext_value_2)) shift_right(&ext_value_2, 1);
                width_dec2 = get_first_non_zero_extBit(ext_value_2);
                if (!is_less_no_sign(tmp, ext_value_2) || is_equal_no_sign(tmp, ext_value_2)) subtraction_no_sign(tmp, ext_value_2, &tmp);
                if (width_dec2 <= width_dec1) break;
            }
            if (is_less_no_sign(tmp, ext_value_2)) {
                step_to_shift = get_first_non_zero_extBit(ext_value_2) - get_first_non_zero_extBit(tmp);
                shift_right(&ext_value_2, step_to_shift);
                if (is_less_no_sign(tmp, ext_value_2)) shift_right(&ext_value_2, 1);
                width_dec2 = get_first_non_zero_extBit(ext_value_2);
                if (width_dec2 < width_dec1) break;
            }
        }
        error = equate_extdec_to_dec(tmp, result);
        setScale(high_scale, result);
        if (Sign_for_save) {
            setSign(result, 1);
        } else {
            setSign(result, 0);
        }
    } else {
        error = error_nan;
    }
    return error;
}
