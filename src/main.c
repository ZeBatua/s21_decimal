#include "s21_decimal.h"

int main() {
    s21_decimal d1 = {0}, d2 = {0}, d3 = {0};
    string_to_decimal(
        "00000000000000000000000000000000 11111111111111111111111111111111 "
        "11111111111111111111111111111111 11111111111111111111111111111111",
        &d1);
    string_to_decimal(
        "00000000000000010000000000000000 00000000000000000000000000000000 "
        "00000000000000000000000000000000 00000000000000000000000000000010",
        &d2);
    int a = s21_add(d1, d2, &d3);
    printf("----------------------------\n\n");
    smart_print_binary_decimal(d3);

    printf("%d\n", a);
    // smart_print_binary_decimal(result);





    // s21_decimal dec1;
    // init_decimal(&dec1);
    // dec1.bits[3] = 0;
    // dec1.bits[2] = 0;
    // dec1.bits[1] = 0;
    // dec1.bits[0] = 0;
    // setScale(0, &dec1);
    // setSign(&dec1, 0);

    // float some = 1234566;
    // printf("%f\n", some / 10);

    // float test_float = 2.5;
    // int test = 0;
    //----------s21_from_float_to_decimal---------//
    // smart_print_binary_decimal(dec1);
    // s21_from_float_to_decimal(test_float, &dec1);
    // smart_print_binary_decimal(dec1);
    // s21_from_decimal_to_int(dec1, &test);
    // printf("int = %d\n", test);

    //----------s21_from_decimal_to_float---------//
    // test_float = 0;
    // smart_print_binary_decimal(dec1);
    // s21_from_decimal_to_float(dec1, &test_float);
    // printf("float = %f\n", test_float);

    return 0;
}

/* 
0 - [0; 31]  
1 - [32, 63]
2 - [64; 95]
3 - [96; 127]
4 - [128; 159]
5 - [160; 191]
6 - [192; 223]
7 - [224; 255]
8 - [256; 287]
9 - [288; 319]
*/