#include "s21_decimal.h"

int main() {
    s21_decimal dec1;
    init_decimal(&dec1);
    // dec1.bits[3] = 0;
    // dec1.bits[2] = 0;
    // dec1.bits[1] = 0;
    // dec1.bits[0] = 123456;
    // setScale(2, &dec1);
    // setSign(&dec1, 1);

    float test_float = 1.5;
    int test = 0;

    printf("%d\n", s21_from_float_to_decimal(test_float, &dec1));
    smart_print_binary_decimal(dec1);
    s21_from_decimal_to_int(dec1, &test);
    printf("int = %d\n", test);
    return 0;
}
