#include "s21_decimal.h"
#include <limits.h>

int main() {
    int num1 = -10;
    int num2 = -10;
    int prod_int = 100;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    smart_print_binary_decimal(a);
    s21_from_int_to_decimal(num2, &b);
    smart_print_binary_decimal(b);
    s21_decimal res_dec = {0};
    int res_int = 0;
    s21_mul(a, b, &res_dec);
    smart_print_binary_decimal(res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    printf("int = %d\n", res_int);
    // ck_assert_int_eq(res_int, prod_int);

    printf("\nd3\n-----------------------------------------------------------------------------------------------------------------------------------\n");
    // smart_print_binary_decimal(*p_res);
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("result1[0] = %d\n", result1.bits[0]);
    // printf("scale = %d\n", getScale(*p_res));
    // printf("add = %d\n", add);

    return 0;
}