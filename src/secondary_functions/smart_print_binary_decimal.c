#include "../s21_decimal.h"

void smart_print_binary_decimal(s21_decimal dec) {
    int mass[128] = {0};
    decimal_to_binary_mass(dec, mass);
    print_binary_decimal(mass);
}
