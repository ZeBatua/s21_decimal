#include "s21_decimal.h"

int main() {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 6771;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12599;
    setScale(0, &dec1);
    
    s21_decimal result;
    init_decimal(&result);
    
    smart_print_binary_decimal(dec1);
    printf("\n");
    // s21_round(dec1, &result);

    // setSign(&dec1, 0);

    // smart_print_binary_decimal(result);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 55;
    
    // setScale(1, &dec2);
    // setSign(&dec2, 0);

    s21_decimal result1;
    init_decimal(&result1);
    

    // smart_print_binary_decimal(dec2);
    printf("\n");
    // s21_round(dec2, &result1);

    smart_print_binary_decimal(dec2);

    printf("this is equality - %d\n", s21_is_equal(dec1, dec2));



    printf("0 = %d\n", result.bits[0]);
    printf("1 = %d\n", result.bits[1]);
    printf("2 = %d\n", result.bits[2]);
    printf("3 = %d\n", result.bits[3]);
    printf("scale = %d\n", getScale(result));
    
    return 0;
}
