#include "../../s21_decimal.h"

void compare_scale_for_div(s21_extended_decimal *divinded, s21_extended_decimal *divider);
int get_width(s21_extended_decimal decimal);
void get_needed_value_from_devinded(s21_extended_decimal *decimal, int width);
int subtraction_for_div(s21_extended_decimal *minuend, s21_extended_decimal subtrahend, s21_extended_decimal *result);
void set_next_digit(s21_extended_decimal *decimal, s21_extended_decimal start_decimal, int digit_position);


int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    s21_extended_decimal ext_value_1 = {0}, buf_value_1 = {0}, ext_value_2 = {0}, ext_result = {0};
    s21_extended_decimal zero = {0};
    equate_dec_to_extdec(value_1, &ext_value_1);
    equate_dec_to_extdec(value_2, &ext_value_2);
    equate_dec_to_extdec(value_2, &buf_value_1);
    equate_dec_to_extdec(*result, &ext_result);
    compare_scale_for_div(&ext_value_1, &ext_value_2);
    int f_width = 0, s_width = 0, difference_width = 0;
    int subtraction_error = 0; 
    s21_extended_decimal subtraction_times = {0};
    s_width = get_width(ext_value_2);
    int bred_counter = 0;

    while (1) {
        f_width = get_width(ext_value_1);
        difference_width = s_width - f_width;
        get_needed_value_from_devinded(&ext_value_1, difference_width);

        subtraction_error = subtraction_for_div(&ext_value_1, ext_value_2, &subtraction_times);
        if (subtraction_error) {
            equate_extdec(buf_value_1, &ext_value_1);
            difference_width -= 1;
            subtraction_for_div(&ext_value_1, ext_value_2, &subtraction_times);
        }
        if (difference_width > 1) {
            f_width -= 1;
            multiply_extdec_by_ten(&ext_value_1);
            set_next_digit(&ext_value_1, buf_value_1, difference_width);

        }
        if (is_equal_no_sign(ext_value_1, zero) || bred_counter > 28) break;
        bred_counter++;
    }
    division_by_ten(&subtraction_times);
    equate_extdec_to_dec(subtraction_times, result);

    return error;
}

void compare_scale_for_div(s21_extended_decimal *divinded, s21_extended_decimal *divider) {
    int scale = getExtScale(*divider);
    while (scale > 0) {
        multiply_extdec_by_ten(divider);
        multiply_extdec_by_ten(divinded);
    }
}

int get_width(s21_extended_decimal decimal) {
    int width = 0;
    s21_extended_decimal zero = {0};
    while(!is_equal_no_sign(decimal, zero)) {
        division_by_ten(&decimal);
        width++;
    }
    return width;
}

void get_needed_value_from_devinded(s21_extended_decimal *decimal, int width) {
    while (width > 0) {
        division_by_ten(decimal);
    }
}

int subtraction_for_div(s21_extended_decimal *minuend, s21_extended_decimal subtrahend, s21_extended_decimal *result) {
    int error = 0;
    s21_extended_decimal zero = {0};
    sub_no_equote(*minuend, subtrahend, minuend);
    if (is_less_no_sign(*minuend, zero)) {
        error = 1;
    } else {
        s21_extended_decimal subtraction_times = {0};
        result->extBits[0] = 1;
        while(is_less_no_sign(*minuend, zero)) {
            sub_no_equote(*minuend, subtrahend, minuend);
            result->extBits[0]++;
        }
    }
    multiply_extdec_by_ten(result);
    return error;
}

void set_next_digit(s21_extended_decimal *decimal, s21_extended_decimal start_decimal, int digit_position) {
    s21_extended_decimal full_decimal = {0};
    equate_extdec(start_decimal, &full_decimal);

    while (digit_position - 1 > 0) {
        division_by_ten(&start_decimal);
    }
    sub_no_equote(full_decimal, start_decimal, &start_decimal);
    add_no_equote(*decimal, start_decimal, decimal);
}