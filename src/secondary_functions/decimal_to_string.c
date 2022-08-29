#include "../s21_decimal.h"

void decimal_to_string(s21_decimal decimal, char *str) {
    for (int j = 3; j >= 0; j--) {
        for (int i = 31; i >= 0; i--) {
            long mask = pow(2, i);
            if (decimal.bits[j] & mask)
                *str = '1';
            else
                *str = '0';
            str++;
        }
        *str = ' ';
        str++;
    }
    str--;
    *str = '\0';
}
