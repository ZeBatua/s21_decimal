#include "s21_decimal.h"

int main() {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;
    setScale(0, &dec1);
    setSign(&dec1, 0);

    // float some = 1234566;
    // printf("%f\n", some / 10);

    float test_float = 2.5;
    int test = 0;
    //----------s21_from_float_to_decimal---------//
    smart_print_binary_decimal(dec1);
    s21_from_float_to_decimal(test_float, &dec1);
    smart_print_binary_decimal(dec1);
    s21_from_decimal_to_int(dec1, &test);
    printf("int = %d\n", test);

    //----------s21_from_decimal_to_float---------//
    // test_float = 0;
    // smart_print_binary_decimal(dec1);
    // s21_from_decimal_to_float(dec1, &test_float);
    // printf("float = %f\n", test_float);

    return 0;
}
