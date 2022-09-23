#include <stdio.h>
#include "s21_decimal.h"

int main() {
    s21_decimal dec1, dec2, result1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0b11111111111111111110001111111111;
    dec1.bits[0] = 0b11111111111111111111111111111111;

    
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b100010001001110001110001001; // 1111111111111000101

    init_decimal(&result1);

    s21_mod(dec1, dec2, &result1);

    smart_print_binary_decimal(result1);

    printf("result\n00000000000000000000000000000000 00000000000000000000000000000000 00000010000100010111010111100101\n");

    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b11111110011111111100110011111;

    
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b10001110001001; // 1111111111111000101

    init_decimal(&result1);

    s21_mod(dec1, dec2, &result1);

    smart_print_binary_decimal(result1);

    printf("result\n00000000000000000000000000000000 00000000000000000000000000000000 00000000000000000000101000000001\n");


    float c = fmod(125, -1.235);
    printf("%f", c);
    // init_decimal(&dec1);
    // dec1.bits[3] = 0;
    // dec1.bits[2] = 0;
    // dec1.bits[1] = 0;
    // dec1.bits[0] = 0b000000001000000000000000000111100;

    
    // init_decimal(&dec2);
    // dec2.bits[3] = 0;
    // dec2.bits[2] = 0;
    // dec2.bits[1] = 0;
    // dec2.bits[0] = 0b000000001000000000000000000111100;

    // init_decimal(&result1);

    // s21_mod(dec1, dec2, &result1);

    // smart_print_binary_decimal(result1);

    // printf("result\n00000000000000000000000000000000 00000000000000000000000000000000 00000000000000000000000000000000\n");

    // init_decimal(&dec1);
    // dec1.bits[3] = 0;
    // dec1.bits[2] = 0;
    // dec1.bits[1] = 0b00000000000000000000000000001100;
    // dec1.bits[0] = 0b11111100100011000000111000111000;

    
    // init_decimal(&dec2);
    // dec2.bits[3] = 0;
    // dec2.bits[2] = 0;
    // dec2.bits[1] = 0;
    // dec2.bits[0] = 0b00000000000000000001010101000101;

    // init_decimal(&result1);
    // printf("55776644664 / 5445\n");
    // s21_mod(dec1, dec2, &result1);

    // smart_print_binary_decimal(result1);

    // printf("result\n00000000000000000000000000000000 00000000000000000000000000000000 00000000000000000000110000001100\n");

    // init_decimal(&dec1);
    // dec1.bits[3] = 0;
    // dec1.bits[2] = 0b00000000011000000000000000001100;
    // dec1.bits[1] = 0b00000000011000000000000000001100;
    // dec1.bits[0] = 0b11111100100011000000111000111000;

    
    // init_decimal(&dec2);
    // dec2.bits[3] = 0;
    // dec2.bits[2] = 0;
    // dec2.bits[1] = 0;
    // dec2.bits[0] = 0b00000000000000010001010101000101;

    // init_decimal(&result1);
    // printf("55776644664 / 70981\n");
    // s21_mod(dec1, dec2, &result1);

    // smart_print_binary_decimal(result1);

    // printf("result\n00000000000000000000000000000000 00000000000000000000000000000000 00000000000000000001100000000101\n");

}


