#include "s21_decimal.h"

int main() {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 2147483648;
    dec1.bits[2] = 4294967295;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;
    smart_print_binary_decimal(dec1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 4294967295;
    dec2.bits[0] = 0;
    smart_print_binary_decimal(dec2);

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 2147483648;
    my_result.bits[2] = 4294967294;
    my_result.bits[1] = 1;
    my_result.bits[0] = 0;
    smart_print_binary_decimal(my_result);

    s21_decimal result1;
    // 11111111111111111111111111111110 00000000000000000000000000000001 00000000000000000000000000000000
    s21_add(dec1, dec2, &result1);
    printf("URAAAA\n");
    smart_print_binary_decimal(result1);
    smart_print_binary_decimal(my_result);
    eq_add = s21_is_equal(result1, my_result);
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