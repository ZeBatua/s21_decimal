#include "../s21_decimal.h"

void equate_extdec_to_dec(s21_extended_decimal E_decimal, s21_decimal *decimal) {
    init_decimal(decimal);
    decimal->bits[3] = E_decimal.extBits[9];
    decimal->bits[2] = E_decimal.extBits[8];
    decimal->bits[1] = E_decimal.extBits[7];
    decimal->bits[0] = E_decimal.extBits[6];
}
