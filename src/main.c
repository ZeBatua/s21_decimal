#include "s21_decimal.h"

int main() {
    s21_decimal d1 = {0}, d2 = {0}, d3 = {0};
    string_to_decimal(
        "00000000000000000000000000000000 10000000000000000000000000000000 "
        "00000000000000000000000000000000 00000000000000000000000000000001",
        &d1);
    string_to_decimal(
        "00000000000000000000000000000000 10000000000000000000000000000000 "
        "00000000000000000000000000000000 00000000000000000000000000000001",
        &d2);
    int a = s21_add(d1, d2, &d3);
    printf("a = %d\n", a);
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