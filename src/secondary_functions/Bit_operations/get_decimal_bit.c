#include "../../s21_decimal.h"

int get_decimal_bit(s21_decimal decimal, int position) { // мб чар
    int res = 0;
    res = getBit(decimal.bits[position / 32], position % 32);
    return res;
}
