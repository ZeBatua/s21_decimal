#include "s21_decimal.h"

int main() {
    int eq = 9;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000100;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000100;

    s21_decimal result1;
    init_decimal(&result1);

    s21_decimal stock_result;
    stock_result.bits[3] = 0;
    stock_result.bits[2] = 0;
    stock_result.bits[1] = 0;
    stock_result.bits[0] = 0b00000000000000000000000000000001;

    s21_div(dec1, dec2, &result1);
    eq = s21_is_equal(stock_result, result1);
    // ck_assert_int_eq(eq, 1);

    printf("\nresult1\n-----------------------------------------------------------------------------------------------------------------------------------\n");
    smart_print_binary_decimal(result1);
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    // printf("bits[0] = %d\n", dec1.bits[0]);
    // printf("scale = %d\n", getScale(dec1));
    printf("eq = %d\n", eq);

    return 0;
}

// /* 
// 0 - [0; 31]  
// 1 - [32, 63]
// 2 - [64; 95]
// 3 - [96; 127]  | decimal.bits[0]
// 4 - [128; 159] | decimal.bits[1]
// 5 - [160; 191] | decimal.bits[2]
// 6 - [192; 223] 
// 7 - [224; 255]
// 8 - [256; 287]
// 9 - [288; 319] | decimal.bits[4]

// */


// // 792281625142643375935439503365
// // 7922816251426433759354395033


// // 15845632502852867518708790066


// // 79228162514264337593543950335
// // 79228162514264337593543950335
// // 792281625142643375935439503350
// // 79228162514264337593543950336
// // 7922816251426433759354395033
// // 65



// #include <stdio.h>
// #include <math.h>


// void out_float(float f)
// {
//   size_t size = sizeof(f);
//   unsigned char * p = (unsigned char *) &f;
//   p += size-1;
//   int value = 0;
//   int i = 0;
//   while (size--)
//   {
//     int n;
//     for (n=0; n<8; n++)
//     {
//       if ('0' + (*p & 128 ? 1 : 0)){
//           value += pow(2, i);
//       }
//       i++;
//       *p <<= 1;
//     }
//     p--;
//   }
//   printf("value = %d\n", value);
// }

// int main()
// {
//   float f = -123.f;

//   out_float(f);
//   putchar('\n');
//   return 0;
// }




// #include <stdio.h>


// void out_float(float f)
// {
//   size_t size = sizeof(f);
//   unsigned char * p = (unsigned char *) &f;
//   p += size-1;
//   while (size--)
//   {
//     int n;
//     for (n=0; n<8; n++)
//     {
//       putchar('0' + (*p & 128 ? 1 : 0));
//       *p <<= 1;
//     }
//     p--;
//   }
// }


// int main()
// {
//   float f = -118.625f;

//   out_float(f);
//   putchar('\n');
//   return 0;
// }