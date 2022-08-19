#include "../s21_decimal.h"

void setSign(s21_decimal value, int sign) { 
    int mask = 1;
    mask = mask << 31;
    decimal->bits[bait] |= mask;
}
