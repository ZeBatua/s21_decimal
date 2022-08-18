// #include <stdio.h>
// #include <math.h>

// void print_binary(int q);

// int main() {
//   int q, r, n = 123;
//   print_binary(n);
//   printf("start decimal\nq = %d\n\n", n);
  

//   q = (n >> 1) + (n >> 2);
//   print_binary(q);
//   printf("q = (n >> 1) + (n >> 2)\nq = %d\n\n", q);
  

//   q = q + (q >> 4);
//   print_binary(q);
//   printf("q = q + (q >> 4)\nq = %d\n\n", q);
  
//   q = q + (q >> 8);
//   print_binary(q);
//   printf("ALARM q = q + (q >> 8)\nq = %d\n\n", q);

//   q = q + (q >> 16);
//   print_binary(q);
//   printf("q = q + (q >> 16)\nq = %d\n\n", q);

//   q = q >> 3;
//   print_binary(q);
//   printf("q = q >> 3\nq = %d\n\n", q);

//   r = n - (((q << 2) + q) << 1);
//   print_binary(r);
//   printf("r = n - (((q << 2) + q) << 1)\nr = %d\n\n", r);

//   q = q + (r > 9);
//   print_binary(q);
//   printf("q = q + (r > 9)\n\nq = %d\n", q);

//   return q + (r > 9);
// }

// void print_binary(int q) {
//     int buf = q;
//     for (int i = 31; i >= 0; i--) {
//     // if (i == 7 || i == 15 || i == 23) {
//     //     printf(" ");
//     // }
//     if (buf >= pow(2, i)) {
//         printf("1");
//         buf = buf - pow(2, i);
//     } else {
//         printf("0");
//     }
//   }
//   printf("\n");
// }

