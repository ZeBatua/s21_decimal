#include "../s21_decimal.h"

void equate_dec_to_extdec(s21_decimal basic, s21_extended_decimal *E_decimal) {
    init_extended_decimal(E_decimal);
    E_decimal->extBits[9] = basic.bits[3];
    E_decimal->extBits[5] = basic.bits[2];
    E_decimal->extBits[4] = basic.bits[1];
    E_decimal->extBits[3] = basic.bits[0];
}
