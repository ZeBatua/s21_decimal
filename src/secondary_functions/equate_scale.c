#include "../s21_decimal.h"

// int equate_scale(s21_decimal *first_value, s21_decimal *second_value) {
//     int error = 0;
//     int first_scale = getScale(*first_value); // 10
//     int second_scale = getScale(*second_value); // 11
//     int difference = abs(first_scale - second_scale); // 1
//     int first_non_zero_bit_dec1 = get_first_non_zero_bit(*first_value);
//     int first_non_zero_bit_dec2 = get_first_non_zero_bit(*second_value);

//     if (first_scale > second_scale) {
//         if (first_non_zero_bit_dec2 > difference) {
//             for (int i = 0; i < difference; i++) {
//                 multiply_by_ten(second_value);
//             }
//         } else {
//             for (int i = 0; i < difference; i++) {
//                 division_by_ten(first_value); // округление?
//             }
//         }
//     } else if (first_scale < second_scale) {
//         if (first_non_zero_bit_dec1 > difference) {
//             for (int i = 0; i < difference; i++) {
//                 multiply_by_ten(first_value);
//             }
//         } else {
//             for (int i = 0; i < difference; i++) {
//                 division_by_ten(second_value);
//             }
//         }
//     }
//     return error;
// }
