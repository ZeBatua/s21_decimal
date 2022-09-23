#include "../../s21_decimal.h"

void compare_scale_for_div(s21_extended_decimal *divinded, s21_extended_decimal *divider);
int get_width(s21_extended_decimal decimal);
int get_needed_value_from_devinded(s21_extended_decimal *divinded, s21_extended_decimal divider, int width);
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
    equate_extdec(ext_value_1, &buf_value_1);
    equate_dec_to_extdec(*result, &ext_result);
    compare_scale_for_div(&ext_value_1, &ext_value_2);
    //!!!!!/// equate_dec_to_extdec(value_1, &buf_value_1); secomd time 
    equate_extdec(ext_value_1, &buf_value_1);
    printf("f sclae = %d\n", getExtScale(ext_value_1));
    printf("s sclae = %d\n", getExtScale(ext_value_2));
    // 899,19485838

    int f_sign = getExtSign(ext_value_1), s_sign = getExtSign(ext_value_2);
    setExtSign(&ext_value_1, 0);
    setExtSign(&ext_value_2, 0);

    int f_width = 0, s_width = 0, difference_width = 0, scale_length = 0, scale_in_dividend = 0, scale_length2 = 1;
    f_width = get_width(ext_value_1);
    s_width = get_width(ext_value_2);
    difference_width = f_width - s_width;
    int next_digit_counter = difference_width;
    int plus_scale = 0;
    
    int divinded_length = get_width(ext_value_1);
    int dividend_scale = getExtScale(ext_value_1);
    int ti_menia_besish = getScale(value_1);

    int decrease_divinded_length = 0;
    int bug_stop = 0;

    if (is_equal_no_sign(ext_value_2, zero)) {
        error = 3;
    } else if (is_equal_no_sign(ext_value_1, zero)) {
        init_decimal(result);
    } else if (is_equal_no_sign(ext_value_2, one)) {
        while(getExtScale(ext_value_2) > 0) {
            multiply_extdec_by_ten(&ext_value_1);
            setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
            setExtScale(getExtScale(ext_value_2) - 1, &ext_value_2);
        }
        difference_width = get_width(ext_value_1) - get_width(ext_value_2);
        equate_extdec(ext_value_1, &subtraction_times);
        setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
    } else {
        if (is_less_no_sign(ext_value_1, one)) {
            while (getExtScale(ext_value_1) > 0) { // затестить на примере 0.001 / 9999
                multiply_extdec_by_ten(&ext_value_2);
                setExtScale(getExtScale(ext_value_2) - 1, &ext_value_2);
                setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
                // plus_scale++;
            }
            setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
            difference_width = get_width(ext_value_1) - get_width(ext_value_2);
            
        }
        
        scale_in_dividend = getExtScale(ext_value_1);
        plus_scale += get_needed_value_from_devinded(&ext_value_1, ext_value_2,  difference_width);
        dividend_scale = getExtScale(ext_value_1);
        f_width =  get_width(ext_value_1);
        setExtScale(0, &ext_value_2);
        divinded_length = divinded_length - f_width;

        while (bug_stop < 100) { // 9223372036854775808
            subtraction_for_div(&ext_value_1, ext_value_2, &subtraction_times);
            if (divinded_length > 0) {
                multiply_extdec_by_ten(&ext_value_1);
                setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
                set_next_digit(&ext_value_1, buf_value_1, divinded_length); 
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
                set_next_digit(&ext_value_1, buf_value_1, divinded_length);
            }
            if (is_less_no_sign(ext_value_1, ext_value_2) && is_equal_no_sign(ext_value_1, zero) && divinded_length > 0) {
                multiply_extdec_by_ten(&ext_value_1);
                setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
                multiply_extdec_by_ten(&subtraction_times);
                setExtScale(getExtScale(subtraction_times) - 1, &subtraction_times);
                divinded_length -= 1;
                set_next_digit(&ext_value_1, buf_value_1, divinded_length);
            }
            //--- scale from dividend (34,5645 / 2) ---//
            if (scale_length2 > 1) setExtScale(scale_length2, &subtraction_times), scale_length2++;
            if (divinded_length + 1 == scale_in_dividend && s21_is_not_equal(value_1, value_2) && plus_scale == 0) setExtScale(scale_length2, &subtraction_times), scale_length2++;

            //--- scale from divivdend remainder  (42 / 490) ---//
            if (divinded_length == 0 && is_equal_no_sign(ext_value_1, zero)) break;
            if (divinded_length < 0 && scale_length2 == 1) scale_length++, setExtScale(scale_length, &subtraction_times);
            if (divinded_length < 0 && is_equal_no_sign(ext_value_1, zero)) break;
            if (scale_length == 33 || scale_length2 == 33) break;
            // if (scale_length == 28 + plus_scale || scale_length2 == 28 + plus_scale)  break;
            if (bug_stop == 28 && is_less_no_sign(ext_value_1, zero)) {
                error = 2;
                break;
            }
            divinded_length -= 1;
            bug_stop++;

            // printf("main_while\n");
        }
    }
    printf("SCALE = %d\n", getExtScale(subtraction_times));
    printf("plus = %d\n", plus_scale);


    // setExtScale(getExtScale(subtraction_times) + plus_scale, &subtraction_times);
    // printf("SCALE = %d\n", getExtScale(subtraction_times));
    // if (subtraction_times.extBits[8] != 0) error = 2;
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    smart_print_exdec(subtraction_times);
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    if (error == 0) {
        error = equate_extdec_to_dec(subtraction_times, result);
        printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
        smart_print_binary_decimal(*result);
        printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
        smart_print_binary_decimal(*result);
        equate_dec_to_extdec(*result, &subtraction_times);
        while(plus_scale - 1 > 0) {
            division_by_ten(&subtraction_times);
            setExtScale(getExtScale(subtraction_times) + 1, &subtraction_times);
            plus_scale--;
        }
        if (error == 0) error = equate_extdec_to_dec(subtraction_times, result);
    }
    
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
        printf("2\n");
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
    printf("START_get_width\n");
    s21_extended_decimal zero = {0};
    int width = 0;
    int a = 0;
    while(!is_equal_no_sign(decimal, zero) && a != 100) {
        division_by_ten(&decimal);
        a++;
        // printf("%d\n", a);
        width++;
    }
    return width;
}

int get_needed_value_from_devinded(s21_extended_decimal *divinded, s21_extended_decimal divider, int diff_width) { // не робит если 1< 2
    // printf("START_get_needed_value_from_devinded\n");
    s21_extended_decimal buf;
    equate_extdec(*divinded, &buf);
    int buf_diff_width = diff_width;

    int mul10 = 0;
    if (diff_width < 0) {
        while (is_less_no_sign(*divinded, divider)) {
            multiply_extdec_by_ten(divinded);
            setExtScale(getExtScale(*divinded) - 1, divinded);
            mul10++;
        }
    } else if (diff_width > 0) {
        while (diff_width > 0) {
            division_by_ten(divinded);
            diff_width--;
        }
        int check_too_few_value = 0;
        if (is_less_no_sign(*divinded, divider)) check_too_few_value = 1;
        if (check_too_few_value) {
            equate_extdec(buf, divinded);
            diff_width = buf_diff_width;
            while (diff_width - 1 > 0) {
                division_by_ten(divinded);
                diff_width--;
            }
        }
    } else {
        if (is_less_no_sign(*divinded, divider)) {
            multiply_extdec_by_ten(divinded);
            setExtScale(getExtScale(*divinded) - 1, divinded);
            mul10++;
        }
    }

    //     int check = 0;
    //     if (!is_less_no_sign(*divinded, divider) && !is_equal_no_sign(*divinded, divider)) {
    //         equate_extdec(buf, divinded);
    //         while (width - 1 > 0) {
    //             division_by_ten(divinded);
    //             printf("8\n");
    //             width--;
    //         }
    //         check = 1;
    //     }
    //     if (is_equal_no_sign(divider, *divinded)) {
    //     } else if ((width + 1 == get_width(*divinded) && width + 1 == get_width(divider)) && !is_less_no_sign(divider, *divinded)) {
    //         multiply_extdec_by_ten(divinded);
    //         setExtScale(getExtScale(*divinded) - 1, divinded);

    //     } else {
    //         while (width > 0 && check != 1) {
    //             division_by_ten(divinded);
    //             printf("5\n");
    //             width--;
    //         }
    //     }
    // }
    return mul10;
}

int subtraction_for_div(s21_extended_decimal *minuend, s21_extended_decimal subtrahend, s21_extended_decimal *result) {
    // printf("START_subtraction_for_div\n");
    int width_before = get_width(*minuend), width_after = 0, get_difference = 0;
    s21_extended_decimal zero = {0}, one = {0};
    one.extBits[0] = 1;
    setExtSign(&one, getExtSign(*result));
    multiply_extdec_by_ten(result);
    setExtScale(getExtScale(*result) - 1, result);
    int bug_stop = 0;
    while(!is_equal_no_sign(*minuend, zero) && bug_stop != 10) {
        printf("10\n");
        sub_no_equote(*minuend, subtrahend, minuend);
        add_no_equote(*result, one, result);
        // smart_print_exdec(*minuend);
        if (is_less_no_sign(*minuend, subtrahend) && !is_equal_no_sign(*minuend, zero)) {
            break;
        }
        bug_stop++;
        // exit(0);
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
            printf("19\n");
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
// 40862548488990303206999699535 2854586852