#include "s21_decimal.h"
#include <limits.h>
#define MAX_INT 2147483647
#define S21_MAX_UINT 4294967295

int main() {
  s21_decimal d1, d2, d3, res;
  string_to_decimal(
      "10000000000000010000000000000000 00000000000000000000000000000000 "
      "00000000000000000000000000000000 00000000000000000000000000001111",
      &d1);
  s21_floor(d1, &d3);
  // decimal_to_string(d3, res);
  // ck_assert_str_eq(
  //     res,
  //     "10000000000000010000000000000000 00000000000000000000000000000000 "
  //     "00000000000000000000000000000000 00000000000000000000000000010100");

  printf(
      "\nd3\n------------------------------------------------------------------"
      "-----------------------------------------------------------------\n");
  smart_print_binary_decimal(d3);
  printf("---------------------------------------------------------------------"
         "--------------------------------------------------------------\n");
  // printf("result1[0] = %d\n", result1.bits[0]);
  // printf("scale = %d\n", getScale(d3));
  // printf("a = %d\n", ex_code);

  return 0;
}