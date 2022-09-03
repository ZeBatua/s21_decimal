#include "../s21_decimal.h"

int getExtSign(s21_extended_decimal value) { 
    return getBit(value.extBits[9], 31);
}
