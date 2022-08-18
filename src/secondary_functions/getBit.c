#include "../s21_decimal.h"

int getBit(int decimal, int position) {
    int result = 0;
    decimal = decimal >> position;
    if (decimal & 1) {
        result = 1;
    } 
    return result;
}
