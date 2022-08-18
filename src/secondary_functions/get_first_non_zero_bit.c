#include "../s21_decimal.h"

int get_first_non_zero_bit(s21_decimal dec) {
    int bit = 0, counter = 0;
    for (int i = 95; i >= 0 && bit != 1; i--) {
        counter++;
        if (get_decimal_bit(dec, i) == 1) {
            bit = 1;
        }
    }
    return counter;
}