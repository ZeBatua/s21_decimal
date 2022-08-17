// #include <stdio.h>
// #include <math.h>

// int main() {
//   int q, r, n = 16;
//   q = (n >> 1) + (n >> 2);
//   printf("q = (n >> 1) + (n >> 2)\nq = %d\n", q);
//   //---------
//   int buf = q;
//   for (int i = 31; i >= 0; i--) {
//     if (buf >= pow(2, i)) {
//         printf("1");
//         buf = buf - pow(2, i);
//     } else {
//         printf("0");
//     }
//   }
//   //---------
//   q = q + (q >> 4);
//   //---------
//   printf("\nq = q + (q >> 4)\nq = %d\n", q);
//   buf = q;
//   for (int i = 31; i >= 0; i--) {
//     if (buf >= pow(2, i)) {
//         printf("1");
//         buf = buf - pow(2, i);
//     } else {
//         printf("0");
//     }
//   }
//   //---------
//   q = q + (q >> 8);
//   //---------
//   printf("\nq = q + (q >> 8)\nq = %d\n", q);
//   buf = q;
//   for (int i = 31; i >= 0; i--) {
//     if (buf >= pow(2, i)) {
//         printf("1");
//         buf = buf - pow(2, i);
//     } else {
//         printf("0");
//     }
//   }
//   //---------
//   q = q + (q >> 16);
//   //---------
//   printf("\nq = q + (q >> 16)\nq = %d\n", q);
//   buf = q;
//   for (int i = 31; i >= 0; i--) {
//     if (buf >= pow(2, i)) {
//         printf("1");
//         buf = buf - pow(2, i);
//     } else {
//         printf("0");
//     }
//   }
//   //---------
//   q = q >> 3;
//   //---------
//   printf("\nq = q >> 3\nq = %d\n", q);
//   buf = q;
//   for (int i = 31; i >= 0; i--) {
//     if (buf >= pow(2, i)) {
//         printf("1");
//         buf = buf - pow(2, i);
//     } else {
//         printf("0");
//     }
//   }
//   //---------
//   r = n - (((q << 2) + q) << 1); 
//   //---------
//   printf("\nr = n - (((q << 2) + q) << 1)\nr = %d\n", r);
//   buf = r;
//   for (int i = 31; i >= 0; i--) {
//     if (buf >= pow(2, i)) {
//         printf("1");
//         buf = buf - pow(2, i);
//     } else {
//         printf("0");
//     }
//   }
//   //---------
//   q = q + (r > 9);
//   //---------
//   printf("\nq = q + (r > 9)\nq = %d\n", q);
//   buf = q;
//   for (int i = 31; i >= 0; i--) {
//     if (buf >= pow(2, i)) {
//         printf("1");
//         buf = buf - pow(2, i);
//     } else {
//         printf("0");
//     }
//   }
//   //---------
//   printf("\n");
//   return q + (r > 9);
// }


