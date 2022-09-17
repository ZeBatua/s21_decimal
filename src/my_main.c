#include <stdio.h>
#include "s21_decimal.h"

int main() {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000010110;

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000011;

    s21_decimal result1;
    init_decimal(&result1);

    s21_mod(dec1, dec2, &result1);

    printf("10100000000000000000000000000000 10000000000000000000000000000000 01111111111111111111111111111111");
}


