//тетрадь 11934/27















#include "../../s21_decimal.h"

void compare_scale_for_div(s21_extended_decimal *divinded, s21_extended_decimal *divider);
int get_width(s21_extended_decimal decimal);
void get_needed_value_from_devinded(s21_extended_decimal *divinded, s21_extended_decimal divider, int width);
int subtraction_for_div(s21_extended_decimal *minuend, s21_extended_decimal subtrahend, s21_extended_decimal *result);
void set_next_digit(s21_extended_decimal *decimal, s21_extended_decimal START_decimal, int digit_position);


int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) { // сделать обработку знаков в начале и в конце
    int error = 0;
    s21_extended_decimal ext_value_1 = {0}, buf_value_1 = {0}, ext_value_2 = {0}, ext_result = {0};
    s21_extended_decimal zero = {0};
    equate_dec_to_extdec(value_1, &ext_value_1);
    equate_dec_to_extdec(value_2, &ext_value_2);
    equate_dec_to_extdec(value_1, &buf_value_1);
    equate_dec_to_extdec(*result, &ext_result);
    compare_scale_for_div(&ext_value_1, &ext_value_2);
    int f_width = 0, s_width = 0, difference_width = 0;
    int subtraction_error = 0; 
    s21_extended_decimal subtraction_times = {0};
    s_width = get_width(ext_value_2);
    int bred_counter = 0;

    while (bred_counter < 30) {
        f_width = get_width(ext_value_1); // убедиться что ширина считается правильно
        difference_width = f_width - s_width;
        get_needed_value_from_devinded(&ext_value_1, ext_value_2,  difference_width); // div by ten ext_value_1

        subtraction_error = subtraction_for_div(&ext_value_1, ext_value_2, &subtraction_times); // try to substract
        if (subtraction_error) {
            equate_extdec(buf_value_1, &ext_value_1);
            difference_width -= 1;
            get_needed_value_from_devinded(&ext_value_1, ext_value_2, difference_width);
            subtraction_for_div(&ext_value_1, ext_value_2, &subtraction_times);
        }
        if (difference_width > 1) {
            f_width -= 1; //зочем
            multiply_extdec_by_ten(&ext_value_1);
            setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
            set_next_digit(&ext_value_1, buf_value_1, difference_width);

        }
        if (is_equal_no_sign(ext_value_1, zero) || bred_counter > 28) break;
        bred_counter++;
        printf("main_while\n");
    }
    division_by_ten(&subtraction_times);
    equate_extdec_to_dec(subtraction_times, result);

    return error;
}

void compare_scale_for_div(s21_extended_decimal *divinded, s21_extended_decimal *divider) {
    printf("START_compare_scale_for_div\n");
    int check_minus_scale1 = 0, check_minus_scale2 = 0; 
    while (getExtScale(*divider) > 0) {
        check_minus_scale1 = setExtScale(getExtScale(*divinded) - 1, divinded);
        check_minus_scale2 = setExtScale(getExtScale(*divider) - 1, divider);
        if (check_minus_scale1) {
            multiply_extdec_by_ten(divinded);
            setExtScale(getExtScale(*divinded) - 1, divinded);
        }
        if (check_minus_scale2) {
            multiply_extdec_by_ten(divider);
            setExtScale(getExtScale(*divider) - 1, divider);
        }
        check_minus_scale1 = 0, check_minus_scale2 = 0; 
        printf("compare_scale_for_div\n");
    }
}

int get_width(s21_extended_decimal decimal) {
    printf("START_get_width\n");
    int width = 0;
    smart_print_exdec(decimal);
    s21_extended_decimal zero = {0};
    // smart_print_exdec(decimal);
    while(!is_equal_no_sign(decimal, zero)) {
        division_by_ten(&decimal);
        // smart_print_exdec(decimal);

        width++;
        if (width > 20) exit(0);
        // printf("get_width\n");
    }
    return width;
}

void get_needed_value_from_devinded(s21_extended_decimal *divinded, s21_extended_decimal divider, int width) {
    printf("START_get_needed_value_from_devinded\n");
    if (width > 0) width -= 1;
    while (width > 0) {
        division_by_ten(divinded);
        width--;
        printf("width = %d\n", width);
        // printf("get_needed_value_from_devinded\n");
    }
    multiply_extdec_by_ten(&divider);
    setExtScale(getExtScale(divider) - 1, &divider);

    if (is_less_no_sign(*divinded, divider)) {
    } else {
        division_by_ten(divinded);
    }
    division_by_ten(&divider);
}

int subtraction_for_div(s21_extended_decimal *minuend, s21_extended_decimal subtrahend, s21_extended_decimal *result) {
    printf("START_subtraction_for_div\n");
    int error = 0;
    s21_extended_decimal zero = {0}, one = {0};
    one.extBits[0] = 1;
    setExtSign(&one, getExtSign(*result));
    sub_no_equote(*minuend, subtrahend, minuend);
    if (is_less_signed(*minuend, zero)) {
        error = 1;
    } else {
        s21_extended_decimal subtraction_times = {0};
        add_no_equote(*result, one, result);

        while(!is_equal_no_sign(*minuend, zero)) {
            sub_no_equote(*minuend, subtrahend, minuend);
            add_no_equote(*result, one, result);
            if (is_less_no_sign(*minuend, subtrahend) && !is_equal_no_sign(*minuend, zero)) {
                sub_no_equote(subtrahend , *minuend, minuend);
                // setExtSign(minuend, 1);
                break;
            }
            printf("subtraction_for_div\n");
        }
        // if (is_less_signed(*minuend, zero)) {
        //     setExtSign(minuend, 0);
        //     sub_no_equote(*result, one, result);
        // }
    }
    multiply_extdec_by_ten(result);
    setExtScale(getExtScale(*result) - 1, result);
    return error;
}

void set_next_digit(s21_extended_decimal *decimal, s21_extended_decimal START_decimal, int digit_position) {
    printf("START_set_next_digit\n");
    s21_extended_decimal full_decimal = {0};
    equate_extdec(START_decimal, &full_decimal);

    while (digit_position - 1 > 0) {
        division_by_ten(&START_decimal);
        division_by_ten(&full_decimal);
        digit_position--;
        printf("set_next_digit\n");
    }
    division_by_ten(&START_decimal);
    multiply_extdec_by_ten(&START_decimal);
    sub_no_equote(full_decimal, START_decimal, &START_decimal);
    add_no_equote(*decimal, START_decimal, decimal);
}
