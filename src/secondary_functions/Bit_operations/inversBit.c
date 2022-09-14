#include "../../s21_decimal.h"

void inversBit(int *decimal, int position) {
    int mask = 1;
    mask = mask << position;
    *decimal ^= mask;  
}
