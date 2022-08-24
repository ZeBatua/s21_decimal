#include "s21_decimal.h"

int main() {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 1;
    dec1.bits[1] = 1;
    dec1.bits[0] = 1;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 1;
    dec2.bits[1] = 1;
    dec2.bits[0] = 1;

    printf("%d\n", s21_is_greater_or_equal(dec1, dec2));
    
    // smart_print_binary_decimal(dec2);

    // printf("this is equality - %d\n", s21_is_equal(dec1, dec2));



    // printf("0 = %d\n", result.bits[0]);
    // printf("1 = %d\n", result.bits[1]);
    // printf("2 = %d\n", result.bits[2]);
    // printf("3 = %d\n", result.bits[3]);
    // printf("scale = %d\n", getScale(result));
    
    return 0;
}
