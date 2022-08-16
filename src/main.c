// сложение гавно
// умнодение степени не работает с дельтой
// тесты
// покрытие ошибок 
// умножение на 10 не актуально в случае переполнения. Деление.
// в деление надо только в самом конце скейл менять
// shift должен как то сигналить что переполняется
// затестить вычитание 
// дописать деление на 10


#include "s21_decimal.h"

int main() {
    
    s21_decimal result = {0};
    init_decimal(&result); // -2147483648;
    result.bits[3] = 0;
    result.bits[2] = pow(2, 5) + pow(2, 14);
    result.bits[1] = 128;
    result.bits[0] = 1;
    
    printf("0 = %d\n", result.bits[0]);
    printf("1 = %d\n", result.bits[1]);
    printf("2 = %d\n", result.bits[2]);
    printf("3 = %d\n", result.bits[3]);
    printf("scale = %d\n", getScale(result));

    int mass3[128] = {0};
    decimal_to_binary_mass(result, mass3);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass3[i]);
    }
    printf("\n");    

    //----
    multiply_by_ten(&result);
    //----
    int mass2[128] = {0};
    decimal_to_binary_mass(result, mass2);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass2[i]);
    }
    printf("\n");
    printf("0 = %d\n", result.bits[0]);
    printf("1 = %d\n", result.bits[1]);
    printf("2 = %d\n", result.bits[2]);
    printf("3 = %d\n", result.bits[3]);
    printf("scale = %d\n", getScale(result));
    
    return 0;
}
