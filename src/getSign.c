#include "s21_decimal.h"

int getSign(s21_decimal value) { 
    return getBit(value.bits[3], 31);
}
