// сложение гавно
// умнодение степени не работает с дельтой
// тесты
// покрытие ошибок 
// умножение на 10 не актуально в случае переполнения. Деление.
// в деление надо только в самом конце скейл менять
// shift должен как то сигналить что переполняется
// затестить вычитание 
// дописать деление на 10
// alt  функции не поддерживают разные знаки. И надо ли это вообще.
// set_decimal_bit надо бы потестить а то изменил
// при деление на 10 теряется точность (в случае 2 в 64)
// q = q + (q >> 16); сделать больше
// 956543 9565420 косячное деление на 10
// затестить сложение, вычитание

#include "s21_decimal.h"

int main() {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 32443000;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0;

    s21_decimal result;
    init_decimal(&result);


    alt_add(dec1, dec2, &result);
    smart_print_binary_decimal(result);
    printf("-----------------\n");

    smart_print_binary_decimal(dec1);
    printf(" start decimal\n");
    printf(" decimal = %d\n\n", dec1.bits[0]);

    division_by_ten(&dec1);

    printf("\n");
    printf("0 = %d\n", dec1.bits[0]);
    printf("1 = %d\n", dec1.bits[1]);
    printf("2 = %d\n", dec1.bits[2]);
    printf("3 = %d\n", dec1.bits[3]);
    printf("scale = %d\n", getScale(dec1));
    
    return 0;
}
