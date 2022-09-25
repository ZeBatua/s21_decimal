#include "s21_decimal.h"

int main() {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000011000000111001101;
  dec1.bits[1] = 0;
  dec1.bits[2] = 0;
  dec1.bits[3] = 0b10000000000000000000000000000000;

  s21_decimal dec2;
  dec2.bits[0] = 0b00000000000000000000010011010010;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 0;

  int n1 = -98765;
  int n2 = 1234;

  // s21_decimal dec1 = {0};
  // s21_decimal dec2 = {0};

  // s21_from_int_to_decimal(n1, &dec1);
  // s21_from_int_to_decimal(n2, &dec2);

  s21_decimal res = {0};
  // int int_res = 0;

  // smart_print_binary_decimal(res);
  s21_mod(dec1, dec2, &res);

  smart_print_binary_decimal(dec1);
  smart_print_binary_decimal(dec2);
  smart_print_binary_decimal(res);

  // s21_truncate(dec1, &res1);
  // s21_round(dec1, &res1);

  // s21_mul(dec1, dec2, &res);

  // smart_print_binary_decimal(res);

  return 0;
}
