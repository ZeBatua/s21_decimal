#include "../../s21_decimal.h"

int get_float_bit(float float_value, unsigned int *mask) {
    int result = 0;
    if (float_value * *mask) {
        result = 1;
    }
    *mask = *mask >> 1;
    return result;
}
