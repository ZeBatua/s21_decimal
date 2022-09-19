#include "s21_decimal.h"

int main() {
    s21_decimal d1 = {0}, d2 = {0}, d3 = {0};
    string_to_decimal(
        "00000000000000000000000000000000 00000000000000000000000000000000 "
        "10000000000000000000000000000000 00000000000000000000000000000000",
        &d1);
    string_to_decimal(
        "00000000000000000000000000000000 00000000000000000000000000000000 "
        "00000000000000000000000000000000 00000000000000000000000000000010",
        &d2);
    s21_div(d1, d2, &d3);
    // ck_assert_int_eq(a, 2);

    printf("\nd3\n-----------------------------------------------------------------------------------------------------------------------------------\n");
    smart_print_binary_decimal(d3);
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("result1[0] = %d\n", result1.bits[0]);
    // printf("scale = %d\n", getScale(result1));
    // printf("a = %d\n", a);

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

// немного поиграть с <<. Узанть почему 1 бит вылезает