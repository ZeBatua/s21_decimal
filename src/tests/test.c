#include "../s21_decimal.h"
#include <check.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>


#define S21_EPS 1e-9

// TEST FOR is_equal


START_TEST(test_is_equal1) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;

    ck_assert_int_eq(s21_is_equal(dec1, dec2),
                     0);

} END_TEST

START_TEST(test_is_equal2) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 1;
    dec1.bits[1] = 0;
    dec1.bits[0] = 1;

    setSign(&dec1, 0);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec1.bits[3] = 0;
    dec1.bits[2] = 1;
    dec1.bits[1] = 0;
    dec1.bits[0] = 1;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_equal(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_equal3) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;
    setScale(1, &dec1);
    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;
    setScale(1, &dec2);
    setSign(&dec2, 1);

    ck_assert_int_eq(s21_is_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_equal4) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;
    setScale(1, &dec1);

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;
    setScale(1, &dec2);

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_equal5) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;

    setSign(&dec1, 0);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;

    setSign(&dec2, 1);

    ck_assert_int_eq(s21_is_equal(dec1, dec2),
                     0);
} END_TEST

// START_TEST() {
//     s21_decimal dec1;
//     init_decimal(&dec1);
//     dec1.bits[3] = 0;
//     dec1.bits[2] = 0;
//     dec1.bits[1] = 0;
//     dec1.bits[0] = 12594141;

//     s21_decimal dec2;
//     init_decimal(&dec2);
//     dec1.bits[3] = 0;
//     dec1.bits[2] = 0;
//     dec1.bits[1] = 0;
//     dec1.bits[0] = 12594141;

//     ck_assert_int_eq(s21_is_equal(dec1, dec2),
//                      0);
// } END_TEST

// START_TEST(acos_6) {
//   double num = NAN;
//   long double orig_res = s21_acos(num), our_res = acos(num);
//   int suc = 0;
//   if (isnan(orig_res) && isnan(our_res)) suc = 1;
//   ck_assert_int_eq(1, suc);
// } END_TEST

// START_TEST(acos_7) {
//     ck_assert_ldouble_nan(s21_acos(NAN));
//     ck_assert_ldouble_nan(acos(NAN));
// } END_TEST

// START_TEST(acos_8) {
//     ck_assert_ldouble_nan(s21_acos(NAN));
//     ck_assert_ldouble_nan(acos(NAN));
// } END_TEST

// START_TEST(acos_9) {
//     ck_assert_ldouble_eq_tol(s21_acos(1.0), acos(1.0), S21_EPS);
//     ck_assert_ldouble_eq_tol(s21_acos(-1.0), acos(-1.0), S21_EPS);
// } END_TEST

// START_TEST(acos_10) {
//     ck_assert_ldouble_eq_tol(s21_acos(0.0), acos(0.0), S21_EPS);
//     ck_assert_ldouble_eq_tol(s21_acos(-0.0), acos(-0.0), S21_EPS);
// } END_TEST

// START_TEST(acos_11) {
//     ck_assert_ldouble_eq_tol(s21_acos(-1), acos(-1), S21_EPS);
// } END_TEST

// START_TEST(acos_12) {
//     ck_assert_ldouble_eq_tol(s21_acos(1), acos(1), S21_EPS);
// } END_TEST






int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_is_equal1);
    tcase_add_test(tc1_1, test_is_equal2);
    tcase_add_test(tc1_1, test_is_equal3);
    tcase_add_test(tc1_1, test_is_equal4);
    tcase_add_test(tc1_1, test_is_equal5);
    // tcase_add_test(tc1_1, test_is_equal);
    // tcase_add_test(tc1_1, test_is_equal1);
    // tcase_add_test(tc1_1, test_is_equal1);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
