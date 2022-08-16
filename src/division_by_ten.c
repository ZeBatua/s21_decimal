// #include "s21_decimal.h"

// void division_by_ten(s21_decimal *decimal) {
//     s21_decimal q1, r1, r2;
//     init_decimal(&q1);
//     init_decimal(&r1);
//     init_decimal(&r2);
//     equate_decimal(*decimal, &r1);
//     s21_decimal buf;
//     init_decimal(&q1);
//     init_decimal(&buf);

//     alt_add(shift_right(&r1, 1), shift_right(&r2, 2), &q1);
//     equate_decimal(q1, &buf);
//     alt_add(buf, shift_right(&q1, 4), &q1);
//     equate_decimal(q1, &buf);
//     alt_add(buf, shift_right(&q1, 8), &q1);
//     equate_decimal(q1, &buf);
//     alt_add(buf, shift_right(&q1, 16), &q1);
//     shift_right(&q1, 3);
//     equate_decimal(q1, &buf);

//     alt_add(buf, shift_left(&q1, 2), &q1);
//     shift_left(&q1, 1);
//     equate_decimal(*decimal, &r1);
//     equate_scale(&q1, &r1);
//     alt_sub();


// }