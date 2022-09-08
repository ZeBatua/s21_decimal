#include "../../s21_decimal.h"

void setBit(int value_bit, int *decimal, int position) {
    int mask = 1;
    if (getBit(*decimal, position) != value_bit) {
        mask = mask << position;
        *decimal ^= mask;    
    }
}
