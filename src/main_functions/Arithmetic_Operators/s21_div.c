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
    equate_dec_to_extdec(value_1, &buf_value_1);
    equate_dec_to_extdec(*result, &ext_result);
    compare_scale_for_div(&ext_value_1, &ext_value_2);
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
    
    int divinded_length = get_width(ext_value_1);
    int dividend_scale = getExtScale(ext_value_1);
    int ti_menia_besish = getScale(value_1);

    int decrease_divinded_length = 0;
    int plus_scale = 0;
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

                printf("1\n");
            }
        }
        int plus_scale = 0;
        scale_in_dividend = getExtScale(ext_value_1);
        plus_scale = get_needed_value_from_devinded(&ext_value_1, ext_value_2,  difference_width);
        dividend_scale = getExtScale(ext_value_1);//39614081257132168796771975168
        f_width =  get_width(ext_value_1);
        setExtScale(0, &ext_value_2);
        divinded_length = divinded_length - f_width;// ne trogat

        while (bug_stop < 100) { // 40862548488990303206999699535 // res = 45402831654433670229999666150
                                                                        // 4540283165443367022999966615
            printf("1\n");
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
            if (is_less_no_sign(ext_value_1, ext_value_2) && is_equal_no_sign(ext_value_1, zero) && divinded_length > 0) {
                multiply_extdec_by_ten(&ext_value_1);
                setExtScale(getExtScale(ext_value_1) - 1, &ext_value_1);
                multiply_extdec_by_ten(&subtraction_times);
                setExtScale(getExtScale(subtraction_times) - 1, &subtraction_times);
                divinded_length -= 1;
                set_next_digit(&ext_value_1, buf_value_1, divinded_length); //  next_digit_counter -> divinded_length
            }
            //--- scale from dividend (34,5645 / 2) ---//
            if (scale_length2 > 1) setExtScale(scale_length2, &subtraction_times), scale_length2++;
            if (divinded_length + 1 == scale_in_dividend && s21_is_not_equal(value_1, value_2)) setExtScale(scale_length2, &subtraction_times), scale_length2++;

            //--- scale from divivdend remainder  (42 / 490) ---//
            if (divinded_length == 0 && is_equal_no_sign(ext_value_1, zero)) break;
            if (divinded_length < 0 && scale_length2 == 0) scale_length++, setExtScale(scale_length, &subtraction_times);
            if (divinded_length < 0 && is_equal_no_sign(ext_value_1, zero)) break;
            if (scale_length == 33 || scale_length2 == 33) break;
            if (bug_stop == 28 && is_less_no_sign(ext_value_1, zero)) {
                error = 2;
                break;
            }
            bug_stop++;

            // printf("main_while\n");
        }
    }
    setExtScale(getExtScale(subtraction_times) + plus_scale, &subtraction_times);
    // printf("bug_stop = %d\n", bug_stop);
    if (subtraction_times.extBits[8] != 0) error = 2;
    if (error == 0) {
        error = equate_extdec_to_dec(subtraction_times, result);
        printf("123123131231231312312421421412,DFOMRFPWENF\n");
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

int get_needed_value_from_devinded(s21_extended_decimal *divinded, s21_extended_decimal divider, int width) { // не робит если 1< 2
    // printf("START_get_needed_value_from_devinded\n");
    s21_extended_decimal buf;
    equate_extdec(*divinded, &buf);
    // while (width > 0) {
    //     division_by_ten(divinded);
    //     printf("5\n");
    //     width--;
    // }
    int mul10 = 0;
    if (width < 0) {
        while (is_less_no_sign(*divinded, divider)) {
            multiply_extdec_by_ten(divinded);
            setExtScale(getExtScale(*divinded) - 1, divinded);
            mul10++;
        }
    } else {
        int check = 0;
        if (!is_less_no_sign(*divinded, divider) && !is_equal_no_sign(*divinded, divider)) {
            equate_extdec(buf, divinded);
            while (width - 1 > 0) {
                division_by_ten(divinded);
                printf("8\n");
                width--;
            }
            check = 1;
        }
        if (is_equal_no_sign(divider, *divinded)) {
        } else if ((width + 1 == get_width(*divinded) && width + 1 == get_width(divider)) && !is_less_no_sign(divider, *divinded)) {
            multiply_extdec_by_ten(divinded);
            setExtScale(getExtScale(*divinded) - 1, divinded);

        } else {
            while (width > 0 && check != 1) {
                division_by_ten(divinded);
                printf("5\n");
                width--;
            }
        }
    }
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
        smart_print_exdec(*minuend);
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
