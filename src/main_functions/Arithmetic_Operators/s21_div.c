#include "../../s21_decimal.h"

void compare_scale_for_div(s21_extended_decimal *divinded, s21_extended_decimal *divider);
int get_width(s21_extended_decimal decimal);
void get_needed_value_from_devinded(s21_extended_decimal *divinded, s21_extended_decimal divider, int width);
int subtraction_for_div(s21_extended_decimal *minuend, s21_extended_decimal subtrahend, s21_extended_decimal *result);
void set_next_digit(s21_extended_decimal *decimal, s21_extended_decimal START_decimal, int next_digit_counter);

// add multiply div value
// добавить тесты где делимое меньше делителя
// 0.0005 / 9999
// нужно обрабатывать ,10000000003

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) { // сделать обработку знаков в начале и в конце
    int error = 0;

    s21_extended_decimal ext_value_1 = {0}, buf_value_1 = {0}, ext_value_2 = {0}, ext_result = {0};
    s21_extended_decimal zero = {0}, one = {0}, subtraction_times = {0};
    one.extBits[0] = 1;

    equate_dec_to_extdec(value_1, &ext_value_1);
    equate_dec_to_extdec(value_2, &ext_value_2);
    equate_dec_to_extdec(value_1, &buf_value_1);
    equate_dec_to_extdec(*result, &ext_result);
    compare_scale_for_div(&ext_value_1, &ext_value_2);

    int f_sign = getExtSign(ext_value_1), s_sign = getExtSign(ext_value_2);


    int f_width = 0, s_width = 0, difference_width = 0, scale_length = 0, scale_in_dividend = 0;
    f_width = get_width(ext_value_1);
    s_width = get_width(ext_value_2);
    difference_width = f_width - s_width;
    int next_digit_counter = difference_width;
    
    int divinded_length = get_width(ext_value_1);
    int dividend_scale = getExtScale(ext_value_1);
    int decrease_divinded_length = 0;

    int bug_stop = 0;

    if (is_equal_no_sign(ext_value_2, zero)) {
        error = 3;
    } else if (is_equal_no_sign(ext_value_2, one)) {
        equate_extdec(ext_value_1, &subtraction_times);
        setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
    } else {
        if (is_less_no_sign(ext_value_1, one)) {
            while (getExtScale(ext_value_1) > 0) { // затестить на примере 0.001 / 9999
                multiply_extdec_by_ten(&ext_value_2);
                setExtScale(getExtScale(ext_value_2) - 1, &ext_value_2);
                setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
            }
        }
        get_needed_value_from_devinded(&ext_value_1, ext_value_2,  difference_width); // div by ten ext_value_1
        f_width =  get_width(ext_value_1);
        setExtScale(0, &ext_value_2);
        divinded_length -= f_width - 1;

        while (bug_stop < 100) { // 131072
            subtraction_for_div(&ext_value_1, ext_value_2, &subtraction_times); // try to substract
            divinded_length -= 1;
            // if (decrease_divinded_length == 0) next_digit_counter -= 1;

            if (divinded_length > 0) {
                multiply_extdec_by_ten(&ext_value_1);
                setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
                set_next_digit(&ext_value_1, buf_value_1, divinded_length); //  next_digit_counter -> divinded_length 
                // next_digit_counter--;
            } else if (divinded_length <= 0 && !is_equal_no_sign(ext_value_1, zero)) {
                multiply_extdec_by_ten(&ext_value_1);
                setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
            }
            if (is_less_no_sign(ext_value_1, ext_value_2) && !is_equal_no_sign(ext_value_1, zero)) {
                multiply_extdec_by_ten(&ext_value_1);
                setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
                multiply_extdec_by_ten(&subtraction_times);
                setExtScale(getExtScale(subtraction_times) - 1, &subtraction_times);
                divinded_length -= 1;
                set_next_digit(&ext_value_1, buf_value_1, divinded_length); //  next_digit_counter -> divinded_length
            }
            //--- scale from dividend (34,5645 / 2) ---//
            if (scale_in_dividend > 0) setExtScale(scale_in_dividend, &subtraction_times), scale_in_dividend++;
            if (divinded_length + 1 == dividend_scale) setExtScale(scale_in_dividend, &subtraction_times), scale_in_dividend++;

            //--- scale from divivdend remainder  (42 / 490) ---//
            if (divinded_length == 0 && is_equal_no_sign(ext_value_1, zero)) break;
            if (divinded_length < 0 && scale_in_dividend == 0) scale_length++, setExtScale(scale_length, &subtraction_times);
            if (divinded_length < 0 && is_equal_no_sign(ext_value_1, zero)) break;
            if (scale_length == 33) break;
            bug_stop++;

            // printf("main_while\n");
        }
    }
    // printf("bug_stop = %d\n", bug_stop);

    if (error != 3) error = equate_extdec_to_dec(subtraction_times, result);
    if (f_sign || s_sign) {
        setSign(result, 1);
    } else if (f_sign && s_sign) {
        setSign(result, 0);
    }
     
    return error;
}

void compare_scale_for_div(s21_extended_decimal *divinded, s21_extended_decimal *divider) {
    // printf("START_compare_scale_for_div\n");
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
        // printf("compare_scale_for_div\n");
    }
}

int get_width(s21_extended_decimal decimal) {
    // printf("START_get_width\n");
    s21_extended_decimal zero = {0};
    int width = 0;
    while(!is_equal_no_sign(decimal, zero)) {
        division_by_ten(&decimal);
        width++;
    }
    return width;
}

void get_needed_value_from_devinded(s21_extended_decimal *divinded, s21_extended_decimal divider, int width) { // не робит если 1< 2
    // printf("START_get_needed_value_from_devinded\n");
    if (width > 0) width -= 1;
    while (width > 0) {
        division_by_ten(divinded);
        width--;
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
    // printf("START_subtraction_for_div\n");
    int width_before = get_width(*minuend), width_after = 0, get_difference = 0;
    s21_extended_decimal zero = {0}, one = {0};
    one.extBits[0] = 1;
    setExtSign(&one, getExtSign(*result));
    multiply_extdec_by_ten(result);
    setExtScale(getExtScale(*result) - 1, result);

    while(!is_equal_no_sign(*minuend, zero)) {
        sub_no_equote(*minuend, subtrahend, minuend);
        add_no_equote(*result, one, result);
        if (is_less_no_sign(*minuend, subtrahend) && !is_equal_no_sign(*minuend, zero)) {
            break;
        }
        // printf("subtraction_for_div\n");
    }
    width_after = get_width(*minuend);
    if (is_equal_no_sign(*minuend, zero)) {
        get_difference = width_before;
    } else {
        get_difference = width_before - width_after; 
    }
    return get_difference;
}

void set_next_digit(s21_extended_decimal *decimal, s21_extended_decimal START_decimal, int digit_position) {
    // printf("START_set_next_digit\n");
    if (digit_position > 0) {
        s21_extended_decimal full_decimal = {0};
        equate_extdec(START_decimal, &full_decimal);

        while (digit_position - 1 > 0) {
            division_by_ten(&START_decimal);
            division_by_ten(&full_decimal);
            digit_position--;
            // printf("set_next_digit\n");
        }
        division_by_ten(&START_decimal);
        multiply_extdec_by_ten(&START_decimal);
        sub_no_equote(full_decimal, START_decimal, &START_decimal);
        add_no_equote(*decimal, START_decimal, decimal);
    }
}
// 40862548488990303206999699535
