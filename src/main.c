#include "s21_decimal.h"

int main() {
  s21_decimal dec1;
  dec1.bits[0] = 0b11101100101100110110000010000000;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0;
  dec1.bits[3] = 10;

  smart_print_binary_decimal(dec1);

  s21_decimal res1;
  // s21_truncate(dec1, &res1);
  s21_round(dec1, &res1);
  smart_print_binary_decimal(res1);

  return 0;
}

/*
0 - [0; 31]
1 - [32, 63]
2 - [64; 95]
3 - [96; 127]
4 - [128; 159]
5 - [160; 191]
6 - [192; 223]
7 - [224; 255]
8 - [256; 287]
9 - [288; 319]
*/