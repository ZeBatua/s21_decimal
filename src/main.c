#include "s21_decimal.h"

int main() {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 1259;
    setScale(1, &dec1);
    
    s21_decimal result;
    init_decimal(&result);

    smart_print_binary_decimal(dec1);
    printf("\n");
    s21_round(dec1, &result);

    smart_print_binary_decimal(result);
    printf("0 = %d\n", result.bits[0]);
    printf("1 = %d\n", result.bits[1]);
    printf("2 = %d\n", result.bits[2]);
    printf("3 = %d\n", result.bits[3]);
    printf("scale = %d\n", getScale(result));
    
    return 0;
}
