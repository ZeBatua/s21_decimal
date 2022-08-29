#include "../../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    s21_extended_decimal ext_value;
    equate_dec_to_extdec(value, &ext_value);
    int scale = 0;
    scale = getExtScale(ext_value);
    for (int i = 0; i < scale; i++) {
        division_by_ten(&ext_value);
    }
    equate_extdec_to_dec(ext_value, result);
    return 0;
}
