#include "s21_decimal.h"

int main() {
    s21_decimal d1 = {0}, d2 = {0}, d3 = {0};
    string_to_decimal(
        "00000000000010100000000000000000 00000000000000000000000000000000 "
        "00000000000000000000000000010100 11101111100111100111011110001110",
        &d1);
        printf("first sclae = %d\n", getScale(d1));
    string_to_decimal(
        "00000000000000100000000000000000 00000000000000000000000000000000 "
        "00000000000000000000000000000000 00000000000000000000000100111011",
        &d2);
        printf("second sclae = %d\n", getScale(d2));
        // 28545868519999999999999999999
        // 285458685,2

    s21_div(d1, d2, &d3);
    // ck_assert_int_eq(eq, 1);;
    printf("\nd3\n-----------------------------------------------------------------------------------------------------------------------------------\n");
    smart_print_binary_decimal(d3);
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("result1[0] = %d\n", result1.bits[0]);
    printf("scale = %d\n", getScale(d3));
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