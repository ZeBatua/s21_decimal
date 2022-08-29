#include "../s21_decimal.h"

int get_first_non_zero_extBit(s21_extended_decimal dec) {
    int bit = 0, counter = 0;
    for (int i = 95; i >= 0 && bit != 1; i--) {
        counter++;
        if (get_extdec_bit(dec, i) == 1) {
            bit = 1;
        }
    }
    return counter;
}