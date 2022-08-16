// #include "s21_decimal.h" // мейн для понимания работыnegatice

// int main() {
//     s21_decimal for_negative;
//     s21_decimal result;
//     s21_decimal result2;
//     init_decimal(&result);
//     init_decimal(&result2);
//     init_decimal(&for_negative);
//     for_negative.bits[3] = -2147483648;
//     result.bits[3] = 1234;

//     printf("current sign = %d\n\n", getSign(for_negative));

//     s21_negate(for_negative, &result);
//     printf("negate sign = %d\n", result.bits[3]);
//     printf("current sign = %d\n\n", getSign(result));

//     s21_negate(result, &result2);
//     printf("negate sign = %d\n", result2.bits[3]);
//     printf("current sign = %d\n", getSign(result2));
//     return 0;
// }

// int main() {
//     s21_decimal for_negative;
//     s21_decimal result;
//     s21_decimal result2;
//     init_decimal(&result);
//     init_decimal(&result2);
//     init_decimal(&for_negative);
//     for_negative.bits[3] = -2147483648;
//     result.bits[3] = 1234;

//     printf("current sign = %d\n\n", getSign(for_negative));

//     s21_negate(for_negative, &result);
//     printf("negate sign = %d\n", result.bits[3]);
//     printf("current sign = %d\n\n", getSign(result));

//     s21_negate(result, &result2);
//     printf("negate sign = %d\n", result2.bits[3]);
//     printf("current sign = %d\n", getSign(result2));
//     return 0;
// }

// int main() {
//     s21_decimal for_negative;
//     s21_decimal result;
//     s21_decimal result2;
//     init_decimal(&result);
//     init_decimal(&result2);
//     init_decimal(&for_negative);
//     for_negative.bits[3] = -2147483648;
//     result.bits[3] = 2147483648 * 2 - 1;
//     result.bits[2] = 1;
//     result.bits[1] = 1024;
//     result.bits[0] = 1;
    
//     int mass[128] = {0};
//     decimal_to_binary_mass(result, mass);
//     for (int i = 127; i >= 0; i--) {
//         if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
//             printf(" ");
//         }
//         printf("%d", mass[i]);
//     }
//     printf("\n");
//     printf("scale = %d\n", getScale(result));
//     return 0;
// }

    // //--------------------------------------------//
    // int mass2[128] = {0};
    // decimal_to_binary_mass(*decimal, mass2);
    // printf("\nstart decimal\n");
    // for (int i = 127; i >= 0; i--) {
    //     if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //         printf(" ");
    //     }
    //     printf("%d", mass2[i]);
    // }
    // printf("\n");
    
    // // printf("scale = %d\n\n", getScale(*decimal));
    
    // //--------------------------------------------//
    // int mass[128] = {0};
    // decimal_to_binary_mass(x2_dec, mass);
    // for (int i = 127; i >= 0; i--) {
    //     if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //         printf(" ");
    //     }
    //     printf("%d", mass[i]);
    // }
    // printf("\n");
    // // printf("scale = %d\n\n", getScale(x2_dec));
    // printf("x2_dec\n");
    // printf("AAAA %d\n",  95 % 32);
    // exit(0);
    // //--------------------------------------------//


//     int main() {
    
//     s21_decimal result = {0};
//     init_decimal(&result); // -2147483648;
//     result.bits[3] = 0;
//     result.bits[2] = pow(2, 5) + pow(2, 14);
//     result.bits[1] = 128;
//     result.bits[0] = 1;
    
//     printf("0 = %d\n", result.bits[0]);
//     printf("1 = %d\n", result.bits[1]);
//     printf("2 = %d\n", result.bits[2]);
//     printf("3 = %d\n", result.bits[3]);
//     printf("scale = %d\n", getScale(result));

//     int mass3[128] = {0};
//     decimal_to_binary_mass(result, mass3);
//     for (int i = 127; i >= 0; i--) {
//         if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
//             printf(" ");
//         }
//         printf("%d", mass3[i]);
//     }
//     printf("\n");    

//     //----
//     division_by_ten(&result);
//     //----
//     int mass2[128] = {0};
//     decimal_to_binary_mass(result, mass2);
//     for (int i = 127; i >= 0; i--) {
//         if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
//             printf(" ");
//         }
//         printf("%d", mass2[i]);
//     }
//     printf("\n");
//     printf("0 = %d\n", result.bits[0]);
//     printf("1 = %d\n", result.bits[1]);
//     printf("2 = %d\n", result.bits[2]);
//     printf("3 = %d\n", result.bits[3]);
//     printf("scale = %d\n", getScale(result));
    
//     return 0;
// }
