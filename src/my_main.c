#include <stdio.h>
#include "s21_decimal.h"

int main() {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000001;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0b00000000000000000000000000000001;
    dec2.bits[0] = 0b01110111010111100110010011111101;

    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
}