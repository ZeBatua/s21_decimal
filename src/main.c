// #include "s21_decimal.h"

// int main() {
//     s21_decimal test = {0};
//     float a = 8;
//     s21_from_float_to_decimal(a, &test);
//     // decimal_to_string(test, res);
//     // ck_assert_str_eq(
//     //     res,
//     //     "10000000000111000000000000000000 00000000000000000000100110011011 "
//     //     "00111001000111000101111000011101 00110101000011100001000001001101");

//     printf("\nd3\n-----------------------------------------------------------------------------------------------------------------------------------\n");
//     smart_print_binary_decimal(test);
//     printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
//     // printf("a = %d\n", a);

//     //-----------------------------------------------------------------------------------------------------------------------------------//
//     // s21_decimal d1 = {0}, d2 = {0}, d3 = {0};
//     // d1.bits[0] = 100;
//     // d2.bits[0] = 22;
//     // int a = s21_mul(d1, d2, &d3);
//     // smart_print_binary_decimal(d3);
//     // printf("bait = %d\n", d3.bits[0]);
//     // printf("a = %d\n", a);



 
//     return 0;
// }

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



#include <stdio.h>
#include <math.h>


void out_float(float f)
{
  size_t size = sizeof(f);
  unsigned char * p = (unsigned char *) &f;
  p += size-1;
  int value = 0;
  int i = 0;
  while (size--)
  {
    int n;
    for (n=0; n<8; n++)
    {
      if ('0' + (*p & 128 ? 1 : 0)){
          value += pow(2, i);
      }
      i++;
      *p <<= 1;
    }
    p--;
  }
  printf("value = %d\n", value);
}

int main()
{
  float f = -123.f;

  out_float(f);
  putchar('\n');
  return 0;
}




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