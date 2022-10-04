#include "../../s21_decimal.h"

int getBinaryExp(float float_value) {
  unsigned int fbits = *((unsigned int *)&float_value);
  unsigned int mask = 0x40000000;  // маска на 30 бит (дознаковый бит)
  int Exp = 0, zero_exp_counter = 0;
  for (int pow_counter = 7; pow_counter >= 0; mask >>= 1, pow_counter--) {
    Exp += pow(2, pow_counter * !!(fbits & mask));
    if (!(fbits & mask)) Exp -= 1, zero_exp_counter++;
  }
  Exp -= 127;
  if (zero_exp_counter == 8) Exp = -126;
  return Exp;
}
