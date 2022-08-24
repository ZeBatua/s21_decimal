#include "../s21_decimal.h"
#include <check.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>


// Возвращаемое значение - код ошибки:
//  - 0 - OK
//  - 1 - ошибка конвертации

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
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594141;

    ck_assert_int_eq(s21_is_equal(dec1, dec2),
                     1);

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
    dec2.bits[3] = 0;
    dec2.bits[2] = 1;
    dec2.bits[1] = 0;
    dec2.bits[0] = 1;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_equal3) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;
    setScale(1, &dec1);
    // setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594141;
    setScale(1, &dec2);
    // setSign(&dec2, 1);

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
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594141;
    setScale(1, &dec2);

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
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
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594141;

    setSign(&dec2, 1);

    ck_assert_int_eq(s21_is_equal(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_equal6) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 12594141;
    dec1.bits[0] = 0;

    // setSign(&dec1, 0);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594141;

    // setSign(&dec2, 1);

    ck_assert_int_eq(s21_is_equal(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_greater_or_equal1) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 1;
    dec1.bits[1] = 1;
    dec1.bits[0] = 1;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 1;
    dec2.bits[1] = 1;
    dec2.bits[0] = 1;

    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_greater_or_equal2) {
 s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 888888;
    dec1.bits[0] = 12594199;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594141;

    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_greater_or_equal3) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 2;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594199;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594141;

    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_greater_or_equal4) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594199;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594141;

    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_greater1) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594199;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594199;

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_greater2) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594198;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594199;

    setSign(&dec2, 1);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_greater3) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594198;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594199;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_greater4) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 2147483646;
    dec1.bits[0] = 2147483646;

    // setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 2147483647;

    // setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_greater5) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 2147483646;
    dec1.bits[0] = 2147483646;

    // setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 2147483646;
    dec2.bits[1] = 2147483646;
    dec2.bits[0] = 2147483647;

    // setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_greater6) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 1234;

    // setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 1234;

    // setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_greater7) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_less_or_equal1) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    setSign(&dec1, 0);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_less_or_equal2) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 241;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_less_or_equal3) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    setSign(&dec1, 0);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 2147483647;
    dec2.bits[1] = 2147483647;
    dec2.bits[0] = 2147483647;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_less_or_equal4) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 2147483647;
    dec1.bits[1] = 2147483647;
    dec1.bits[0] = 2147483647;

    setSign(&dec1, 0);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 2147483647;
    dec2.bits[1] = 2147483647;
    dec2.bits[0] = 2147483647;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_less_or_equal5) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 2147483647;
    dec1.bits[1] = 2147483647;
    dec1.bits[0] = 2147483647;

    setSign(&dec1, 0);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 2147483647;
    dec2.bits[1] = 2147483647;
    dec2.bits[0] = 2147483647;

    setSign(&dec2, 1);

    ck_assert_int_eq(s21_is_greater(dec1, dec2),
                     0);
} END_TEST






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
    tcase_add_test(tc1_1, test_is_equal6);


    tcase_add_test(tc1_1, test_is_greater_or_equal1);
    tcase_add_test(tc1_1, test_is_greater_or_equal2);
    tcase_add_test(tc1_1, test_is_greater_or_equal3);
    tcase_add_test(tc1_1, test_is_greater_or_equal4);


    tcase_add_test(tc1_1, test_is_greater1);
    tcase_add_test(tc1_1, test_is_greater2);
    tcase_add_test(tc1_1, test_is_greater3);
    tcase_add_test(tc1_1, test_is_greater4);
    tcase_add_test(tc1_1, test_is_greater5);
    tcase_add_test(tc1_1, test_is_greater6);
    tcase_add_test(tc1_1, test_is_greater7);

    tcase_add_test(tc1_1, test_is_less_or_equal1);
    tcase_add_test(tc1_1, test_is_less_or_equal2);
    tcase_add_test(tc1_1, test_is_less_or_equal3);
    tcase_add_test(tc1_1, test_is_less_or_equal4);
    tcase_add_test(tc1_1, test_is_less_or_equal5);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
