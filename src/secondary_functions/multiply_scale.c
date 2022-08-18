#include "../s21_decimal.h"

void multiply_by_ten(s21_decimal *decimal) {
    s21_decimal x2_dec, x8_dec;
    init_decimal(&x2_dec);
    init_decimal(&x8_dec);
    equate_decimal(*decimal, &x2_dec);
    equate_decimal(*decimal, &x8_dec);
    int dec_bit = 0;

    shift_left(&x2_dec, 1);
    shift_left(&x8_dec, 3);

    s21_decimal result;
    init_decimal(&result);
    alt_add(x2_dec, x8_dec, &result);
    equate_decimal(result, decimal);
    setScale(getScale(*decimal) + 1, decimal);
}
