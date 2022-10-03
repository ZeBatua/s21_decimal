#include "s21_decimal.h"
#include <limits.h>
#define MAX_INT 2147483647
#define S21_MAX_UINT 4294967295

int main() {
  s21_decimal dec1, dec2, result, orig;
//   int diff = 9;
  init_decimal(&dec1);
  init_decimal(&dec2);
  init_decimal(&result);
  init_decimal(&orig);
  // 4949341991908698119347372159
  dec1.bits[3] = 0;
  dec1.bits[2] = 0b1111111111011111111111101111;
  dec1.bits[1] = 0b111100000000000000;
  dec1.bits[0] = 0b0000000000000001111111;
  // 31
  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 0b000000011111;
  setScale(2, &dec2);
  // 15965619328737735868862490835.4838709677419355
  orig.bits[3] = 0;
  orig.bits[2] = 0b1110011100111001110100011010011;
  orig.bits[1] = 0b10000100100000011100111001110;
  orig.bits[0] = 0b1110011100111001110100011010011;

  printf("bits[3] = %d\n", orig.bits[3]);
  printf("bits[2] = %d\n", orig.bits[2]);
  printf("bits[1] = %d\n", orig.bits[1]);
  printf("bits[0] = %d\n\n", orig.bits[0]);

  printf("2bits[3] = %d\n", result.bits[3]);
  printf("2bits[2] = %d\n", result.bits[2]);
  printf("2bits[1] = %d\n", result.bits[1]);
  printf("2bits[0] = %d\n", result.bits[0]);

  s21_div(dec1, dec2, &result);

  return 0;
}

// 
