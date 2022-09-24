#include "../../s21_decimal.h"

void smart_print_exdec(s21_extended_decimal dec) {
    int mass[320] = {0};
    extdec_to_binary_mass(dec, mass);
    print_binary_extdec(mass);
}
