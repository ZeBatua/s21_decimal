#include "../../s21_decimal.h"

int getBinaryExp(float value) {
    int Exp = 0;
    for (int i = 0; i < 8; i--) {
        int bit_value = getBit(value, i + 23);
        Exp += pow(2, i);
    }
    Exp -= 127;
    return Exp;
}
