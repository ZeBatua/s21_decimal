#include "s21_decimal.h"

int main() {
    // int eq = 9;
    // s21_decimal dec1;
    // init_decimal(&dec1);
    // dec1.bits[3] = 0;
    // dec1.bits[2] = 0b10000100000010001011010100111000;// 100001000000100010110101001110000100000010111100100101110011010100011100010001011011000001001111
    // dec1.bits[1] = 0b01000000101111001001011100110101;
    // dec1.bits[0] = 0b00011100010001011011000001001111;

    // s21_decimal dec2;
    // init_decimal(&dec2);
    // dec2.bits[3] = 0;
    // dec2.bits[2] = 0;
    // dec2.bits[1] = 0;
    // dec2.bits[0] = 0b00000000000000000000000000001001;

    // setScale(1, &dec2);

    // s21_decimal result1;
    // init_decimal(&result1);

    // eq = s21_div(dec1, dec2, &result1);


        int eq = 9;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000100;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000100;

    s21_decimal result1;
    init_decimal(&result1);

    s21_decimal stock_result;
    stock_result.bits[3] = 0;
    stock_result.bits[2] = 0;
    stock_result.bits[1] = 0;
    stock_result.bits[0] = 0b00000000000000000000000000000001;

    s21_div(dec1, dec2, &result1);



// 13620849496330101068999899845s
// 13046182829663434402333233178  // мои 
///13620849496330101068999899845
    // s21_div(dec1, dec2, &result1);
    // eq = s21_is_equal(stock_result, result1);
    // int a = s21_div(d1, d2, &d3);
    // ck_assert_int_eq(a, 2);
        // printf("second sclae = %d\n", getScale(d2));
        // 28545868519999999999999999999
        // 285458685,2

        

    // s21_div(d1, d2, &d3);
    // ck_assert_int_eq(eq, 1);;
    printf("\nd3\n-----------------------------------------------------------------------------------------------------------------------------------\n");
    smart_print_binary_decimal(result1);
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("result1[0] = %d\n", result1.bits[0]);
    printf("scale = %d\n", getScale(result1));
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