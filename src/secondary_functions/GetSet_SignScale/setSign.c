#include "../../s21_decimal.h"

void setSign(s21_decimal *value, int sign) { 
    int mask = 1;
    if (get_decimal_bit(*value, 127) != sign) {
        mask = mask << 31;
        value->bits[3] ^= mask;    
    }
}
