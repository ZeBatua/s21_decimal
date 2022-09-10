#include "s21_decimal.h"

int main() {
    s21_decimal d1 = {0}, d2 = {0}, d3 = {0};
    string_to_decimal(
        "00000000000000000000000000000000 11111111111111111111111111111111 "
        "11111111111111111111111111111111 11111111111111111111111111111111",
        &d1);
    string_to_decimal(
        "00000000000000010000000000000000 00000000000000000000000000000000 "
        "00000000000000000000000000000000 00000000000000000000000000000111",
        &d2);
    int a = s21_add(d1, d2, &d3);
    printf("\n\n\n-----------------------------------------------------------------------------------------------------------------------------------\n");
    smart_print_binary_decimal(d3);
    printf("\n\n\n-----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("a = %d\n", a);

    double value = 66.12387777777779876543223456;
    printf("value = %.30lf\n", value / 10);
    // while (value > 10) {
    //     value = value / 10;
    //     value = round(value);
    // }
    // printf("%f\n", value);

    // while (value > 1) {
    //     value /= 10;
    // }
    // value = round(value);
    // printf("%f", value);
    return 0;
}

/* 
0 - [0; 31]  
1 - [32, 63]
2 - [64; 95]
3 - [96; 127]  | decimal.bits[0]
4 - [128; 159] | decimal.bits[1]
5 - [160; 191] | decimal.bits[2]
6 - [192; 223] 
7 - [224; 255]
8 - [256; 287]
9 - [288; 319] | decimal.bits[4]

*/