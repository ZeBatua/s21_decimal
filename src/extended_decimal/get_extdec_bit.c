#include "../s21_decimal.h"

int get_extdec_bit(s21_extended_decimal E_decimal, int position) { // мб чар
    int res = 0;
    res = getBit(E_decimal.extBits[position / 32], position % 32);
    return res;
}
