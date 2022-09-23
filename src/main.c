#include "s21_decimal.h"
#include <limits.h>
#define MAX_INT 2147483647  

int main() {
    int num1 = 123;
    float num2 = 12.5;
    float origin_float = 110.5;
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_from_int_to_decimal(num1, &a);
    printf("123\n");
    s21_from_float_to_decimal(num2, &b);
    printf("3 = %d\n", b.bits[3]);
    printf("2 = %d\n", b.bits[2]);
    printf("1 = %d\n", b.bits[1]);
    printf("0 = %d\n", b.bits[0]);
    smart_print_binary_decimal(b);
    printf("321\n");
    s21_decimal res_dec = {0};
    float res_float = 0.0;
    s21_sub(a, b, &res_dec);
    s21_from_decimal_to_float(res_dec, &res_float);
    // ck_assert_float_eq(res_float, origin_float);

    printf("\nd3\n-----------------------------------------------------------------------------------------------------------------------------------\n");
    // smart_print_binary_decimal(val);
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("result1[0] = %d\n", result1.bits[0]);
    // printf("scale = %d\n", getScale(*p_res));
    // printf("add = %d\n", add);res_float == 116.6, origin_float == 110.5

    return 0;
}