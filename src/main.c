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
    dec1.bits[0] = 185150;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = -11;

    // alt_sub(dec1, dec2, &result);

    // int mass3[128] = {0};
    // decimal_to_binary_mass(dec1, mass3);
    // for (int i = 127; i >= 0; i--) {
    //     if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //         printf(" ");
    //     }
    //     printf("%d", mass3[i]);
    // }
    printf("AAAAAAAAAA\n");

    int mass10[128] = {0};
    decimal_to_binary_mass(dec2, mass10);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass10[i]);
    }
    printf("\n");

    // int mass11[128] = {0};
    // decimal_to_binary_mass(result, mass11);
    // for (int i = 127; i >= 0; i--) {
    //     if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //         printf(" ");
    //     }
    //     printf("%d", mass11[i]);
    // }
    // printf("\n");


    int mass3[128] = {0};
    decimal_to_binary_mass(dec1, mass3);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass3[i]);
    }
    printf("\n");
    s21_decimal result;
    init_decimal(&result); // -2147483648;
    //----
    division_by_ten(&dec1);
    // shift_right(&dec1, 3);
    //----

    int mass5[128] = {0};
    decimal_to_binary_mass(dec1, mass5);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass5[i]);
    }
    printf("\n");
    printf("0 = %d\n", dec1.bits[0]);
    printf("1 = %d\n", dec1.bits[1]);
    printf("2 = %d\n", dec1.bits[2]);
    printf("3 = %d\n", dec1.bits[3]);
    printf("scale = %d\n", getScale(result));
    
    return 0;
}
