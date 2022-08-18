#include "../s21_decimal.h"

int main() {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 123456;
    setScale(4, &dec1);


    s21_decimal result;
    init_decimal(&result);

    s21_truncate(dec1, &result);

    printf("0 = %d\n", result.bits[0]);
    printf("1 = %d\n", result.bits[1]);
    printf("2 = %d\n", result.bits[2]);
    printf("3 = %d\n", result.bits[3]);
    printf("scale = %d\n", getScale(result));
    
    return 0;
}
