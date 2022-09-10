#include "../../s21_decimal.h"

int getBit(int value, int position) {
    int result = 0;
    value = value >> position;
    if (value & 1) {
        result = 1;
    } 
    return result;
}
