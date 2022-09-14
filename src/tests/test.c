#include "../s21_decimal.h"
#include <check.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>


// Возвращаемое значение:

// 0 - FALSE
// 1 - TRUE

#define S21_EPS 1e-9

// TEST FOR is_equal


START_TEST(test_is_equal1) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 1;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 1;

    for (int y = 0; y < 29; y++) {
        setScale(y, &dec1);
        setScale(y, &dec2);
        if (s21_is_equal(dec1, dec2) != 1) 
            // printf("\n");
            // printf("\n\n\n\n\n%d\n\n\n\n\n\n", y);
            // smart_print_binary_decimal(dec1);
            // smart_print_binary_decimal(dec2);
            continue;
        ck_assert_int_eq(s21_is_equal(dec1, dec2),
                        1);
        }

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

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 12594141;
    setScale(1, &dec2);

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
    dec1.bits[1] = 0;
    dec1.bits[0] = 12594141;


    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 125941423;


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


    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 2147483647;


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

    // setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2),
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

    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_less_or_equal3) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 2147483646;
    dec1.bits[1] = 2147483646;
    dec1.bits[0] = 2147483646;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 2147483646;
    dec2.bits[1] = 2147483646;
    dec2.bits[0] = 2147483646;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2),
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

    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2),
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

    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_less1) {
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
    dec2.bits[2] = 0;
    dec2.bits[1] = 2147483647;
    dec2.bits[0] = 2147483647;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_less(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_less2) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 2147483647;
    dec1.bits[1] = 2147483647;
    dec1.bits[0] = 2147483647;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 2147483647;
    dec2.bits[1] = 2147483647;
    dec2.bits[0] = 2147483647;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_less(dec1, dec2),
                     1); // 0 -> 1
} END_TEST

START_TEST(test_is_less3) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 1;

    setSign(&dec1, 0);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 2147483647;
    dec2.bits[1] = 2147483647;
    dec2.bits[0] = 2147483647;

    setSign(&dec2, 1);

    ck_assert_int_eq(s21_is_less(dec1, dec2),
                     0); // 0 -> 1
} END_TEST

START_TEST(test_is_less4) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 2147483647;
    dec1.bits[1] = 2147483647;
    dec1.bits[0] = 2147483647;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0;

    setSign(&dec2, 1);

    ck_assert_int_eq(s21_is_less(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_less5) {
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

    ck_assert_int_eq(s21_is_less(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_less6) {
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

    ck_assert_int_eq(s21_is_less(dec1, dec2),
                     1);
} END_TEST

// *******************************

START_TEST(test_is_not_equal1) {
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

    ck_assert_int_eq(s21_is_not_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_not_equal2) {
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

    ck_assert_int_eq(s21_is_not_equal(dec1, dec2),
                     0);
} END_TEST

START_TEST(test_is_not_equal3) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 2147483647;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    setSign(&dec1, 0);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 2147483647;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_not_equal(dec1, dec2),
                     1);
} END_TEST

START_TEST(test_is_not_equal4) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 2147483647;

    setSign(&dec1, 1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 2147483647;
    dec2.bits[0] = 0;

    setSign(&dec2, 0);

    ck_assert_int_eq(s21_is_not_equal(dec1, dec2),
                     1);
} END_TEST

// with scale

START_TEST(test_is_not_equal5) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 2147483647;
    dec1.bits[1] = 2147483647;
    dec1.bits[0] = 2147483647;

    setSign(&dec1, 0);
    // setScale(5, &dec1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 2147483647;
    dec2.bits[1] = 2147483647;
    dec2.bits[0] = 2147483647;

    setSign(&dec2, 0);
    
    
    for (int y = 0; y < 28; y++) {
        for (int x = 28; x > -1; x--) {
            setScale(y, &dec1);
            setScale(x, &dec2);
            if (s21_is_not_equal(dec1, dec2) != 1) {
                continue;
            }
            ck_assert_int_eq(s21_is_not_equal(dec1, dec2),
                        1);
        }
    }
    
} END_TEST


// Ariphmetic Operations

START_TEST(test_add1) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 1;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 1;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 2;

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    ck_assert_int_eq(result1.bits[0], my_result.bits[0]);
    
} END_TEST

START_TEST(test_add2) {

    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 2147483648;
    dec1.bits[2] = 0;
    dec1.bits[1] = 22554;
    dec1.bits[0] = 1;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 22554;
    dec2.bits[0] = 1;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0;

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);

    int eq_add = s21_is_equal(result1, my_result);

    ck_assert_int_eq(eq_add, 1);
    
} END_TEST

START_TEST(test_add3) {

    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 88454546;
    dec1.bits[1] = 1;
    dec1.bits[0] = 0;

    // 000001010100010110110101100100100000000000000000000000000000000100000000000000000000000000000000

    s21_decimal dec2;
    init_decimal(&dec2);  // реализация в умножении !!!
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 4294967295;
    dec2.bits[0] = 2;

    // 000000000000000000000000000000001111111111111111111111111111111100000000000000000000000000000010

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 88454547;
    my_result.bits[1] = 0;
    my_result.bits[0] = 2;

    // 000001010100010110110101100100110000000000000000000000000000000000000000000000000000000000000010

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);

    int eq_add = s21_is_equal(result1, my_result);

    ck_assert_int_eq(eq_add, 1);
    
} END_TEST

// TEST FOR INF

START_TEST(test_add4) {

    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0b11111111111111111111111111111111;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0b11111111111111111111111111111111;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0;

    s21_decimal result1;
    init_decimal(&result1);

    ck_assert_int_eq(s21_add(dec1, dec2, &result1), 1);
    
} END_TEST

START_TEST(test_add44) {

    int eq = 9;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0b11111111111111111111111111111111;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0b11111111111111111111111111111111;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0;

    s21_decimal result1;
    init_decimal(&result1);

    s21_decimal stock_result;
    init_decimal(&stock_result);
    stock_result.bits[3] = 0;
    stock_result.bits[2] = 0;
    stock_result.bits[1] = 0;
    stock_result.bits[0] = 0;

    s21_add(dec1, dec2, &result1);
    eq = s21_is_equal(result1, stock_result);
    ck_assert_int_eq(eq, 1);
    
} END_TEST

START_TEST(test_add441) {

    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0b11111111111111111111111111111111;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0b11111111111111111111111111111111;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0;

    s21_decimal result1;
    init_decimal(&result1);

    ck_assert_int_eq(s21_add(dec1, dec2, &result1), 2);
    
} END_TEST


START_TEST(test_add5) {

    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 4294967295;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 4294967295;
    dec2.bits[0] = 0;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 4294967295;
    my_result.bits[1] = 4294967295;
    my_result.bits[0] = 0;

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    int eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);
    
} END_TEST


START_TEST(test_add6) {

    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 2147483648;
    dec1.bits[2] = 4294967295;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 2147483648;
    dec2.bits[2] = 0;
    dec2.bits[1] = 4294967295;
    dec2.bits[0] = 0;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 2147483648;
    my_result.bits[2] = 4294967295;
    my_result.bits[1] = 4294967295;
    my_result.bits[0] = 0;

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    int eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);
    
} END_TEST


START_TEST(test_add7) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 4294967294;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 2147483648;
    dec2.bits[0] = 0;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 4294967295;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0;

    s21_decimal result1;
    s21_add(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST


START_TEST(test_add8) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 54555;  
    dec1.bits[1] = 8559;  
    dec1.bits[0] = 7875;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 2147483648;
    dec2.bits[2] = 7848488;
    dec2.bits[1] = 5455165;
    dec2.bits[0] = 111588;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 2147483648;
    my_result.bits[2] = 7793933;
    my_result.bits[1] = 5446606;
    my_result.bits[0] = 103713;

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_add9) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0b00000000000000001101010100011011;  
    dec1.bits[1] = 0b00000000000000000010000101101111;  
    dec1.bits[0] = 0b00000000000000000001111011000011;

    // setScale(8, &dec1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0b00000000011101111100001000101000;
    dec2.bits[1] = 0b00000000010100110011110100111101;
    dec2.bits[0] = 0b00000000000000011011001111100100;

    // setScale(5, &dec2);

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0b00000000011101101110110100001101;
    my_result.bits[1] = 0b00000000010100110001101111001110;
    my_result.bits[0] = 0b00000000000000011001010100100001;

    // setScale(8, &my_result);

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_add10) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 2147483648;
    dec1.bits[2] = 54555;  
    dec1.bits[1] = 8559;  
    dec1.bits[0] = 7875;

    setScale(22, &dec1);
    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 2147483648;
    dec2.bits[2] = 7848488;
    dec2.bits[1] = 5455165;
    dec2.bits[0] = 111588;

    setScale(22, &dec2); 

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 2147483648;
    my_result.bits[2] = 7903043;
    my_result.bits[1] = 5463724;
    my_result.bits[0] = 119463;

    setScale(22, &my_result);

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_add11) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b10000000000000000000000000000000;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0b00000000000000000000000000000001;
    dec2.bits[0] = 0b10000000000000000000000000000000; 

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0b00000000000000000000000000000001;
    my_result.bits[0] = 0;

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_add12) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b10000000000000000000000000000000;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0b00000000000000000000000000000001;
    dec2.bits[0] = 0b10000000000000000000000000000000; 

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0b00000000000000000000000000000001;
    my_result.bits[0] = 0;

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_add13) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0b00000000000000000000000000000001;
    dec1.bits[0] = 0b11111111111111111111111111111111;

    setScale(1, &dec1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b11111111111111111111111111111111;

    setScale(1, &dec2);

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0b00000000000000000000000000000001;
    my_result.bits[0] = 0;

    setScale(1, &my_result);

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_add14) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0b00000000000000000000000000000001;
    dec1.bits[0] = 0b10000000000000000000000000000000;

    setScale(2, &dec1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b10000000000000000000000000000000;

    setScale(2, &dec2);

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0b00000000000000000000000000000001;
    my_result.bits[0] = 0;

    setScale(2, &my_result);

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

// START_TEST(test_add15) {
//     int eq_add = 0;
//     s21_decimal dec1;
//     init_decimal(&dec1);
//     dec1.bits[3] = 0b10000000000000000000000000000000;
//     dec1.bits[2] = 0;
//     dec1.bits[1] = 0;
//     dec1.bits[0] = 0b00000000000000000000000000000011;

//     setScale(28, &dec1);

//     s21_decimal dec2;
//     init_decimal(&dec2);
//     dec2.bits[3] = 0;
//     dec2.bits[2] = 0;
//     dec2.bits[1] = 0b00000000000000000000000000000001;
//     dec2.bits[0] = 0b10000000000000000000000000000000;

//     setScale(28, &dec2);

//     s21_decimal my_result;
//     init_decimal(&my_result);
//     my_result.bits[3] = 0;
//     my_result.bits[2] = 0;
//     my_result.bits[1] = 0b00000000000000000000000000000001;
//     my_result.bits[0] = 0;

//     setScale(2, &my_result);

//     s21_decimal result1;
//     init_decimal(&result1);

//     s21_add(dec1, dec2, &result1);
//     eq_add = s21_is_equal(result1, my_result);
//     ck_assert_int_eq(eq_add, 1);

// } END_TEST

START_TEST(test_sub4) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;  
    dec1.bits[1] = 0;  
    dec1.bits[0] = 20;

    setScale(0, &dec1);

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 25;

    setScale(0, &dec2); 


    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 2147483648;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 5;


    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_sub5) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 4294967295;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    setScale(22, &dec1);

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 4294967295;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0;

    setScale(22, &dec2); 


    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0;


    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_sub6) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0b11111111111111111111111111111111;
    dec1.bits[1] = 0b11111111111111111111111111111111;
    dec1.bits[0] = 0b11111111111111111111111111111111;

    setScale(0, &dec1);

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0b00011111111111111111111111111111;
    dec2.bits[1] = 0b11111111111111111111111111111111;
    dec2.bits[0] = 0b11111111111111111111111111111111;

    setScale(0, &dec2); 


    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0b11100000000000000000000000000000;
    my_result.bits[1] = 0b00000000000000000000000000000000;
    my_result.bits[0] = 0b00000000000000000000000000000000;


    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    printf("full decimal\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_sub7) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0b10000000000000000000000000000000;
    dec1.bits[1] = 0b10000000000000000000000000000000;
    dec1.bits[0] = 0b10000000000000000000000000000000;

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0b00011111111111111111111111111111;
    dec2.bits[1] = 0b11111111111111111111111111111111;
    dec2.bits[0] = 0b11111111111111111111111111111111;


    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0b10100000000000000000000000000000;
    my_result.bits[1] = 0b10000000000000000000000000000000;
    my_result.bits[0] = 0b01111111111111111111111111111111;

    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    printf("minus minus decimal\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_sub8) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0b10110011001010000110011100110010;
    dec1.bits[1] = 0b00111100101000000110000000010001;
    dec1.bits[0] = 0b01110111010111100110010011111101;

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00100001000111101001110101010101;


    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0b10110011001010000110011100110010;
    my_result.bits[1] = 0b00111100101000000110000000010001;
    my_result.bits[0] = 0b01010110001111111100011110101000;


    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    printf("minus minus decimal\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_sub9) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0b10110011001010000110011100110010;
    dec1.bits[1] = 0b00111100101000000110000000010001;
    dec1.bits[0] = 0b01110111010111100110010011111101;

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0b10110011001010000110011100110010;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00100001000111101001110101010101;

    s21_decimal result1;
    init_decimal(&result1);

    
    ck_assert_int_eq(s21_sub(dec1, dec2, &result1), 2);

} END_TEST

START_TEST(test_sub10) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0b10110011001010000110011100110010;
    dec1.bits[1] = 0b00111100101000000110000000010001;
    dec1.bits[0] = 0b01110111010111100110010011111101;

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0b10110011001010000110011100110010;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00100001000111101001110101010101;

    s21_decimal result1;
    init_decimal(&result1);

    
    ck_assert_int_eq(s21_sub(dec1, dec2, &result1), 2);

} END_TEST

START_TEST(test_sub11) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0b00111100101000000110000000010001;
    dec1.bits[0] = 0b01110111010111100110010011111101;

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0b10110011001010000110011100110010;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00100001000111101001110101010101;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0b10110011001010000110011100110001;
    my_result.bits[1] = 0b11000011010111111001111111101110;
    my_result.bits[0] = 0b10101001110000000011100001011000;

    

    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);    
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_sub12) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b01110111010111100110010011111101;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0b00000000000000000000000000000001;
    dec2.bits[0] = 0b01110111010111100110010011111101;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0b00000000000000000000000000000001;
    my_result.bits[0] = 0;

    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);    
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_sub13) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b11111111111111111111111111111111;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000001;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0b11111111111111111111111111111110;

    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);    
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_sub14) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000001;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b11111111111111111111111111111111;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0b11111111111111111111111111111110;

    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);    
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_sub15) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000001;

    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0b00000000000000000000000000000011;


    s21_decimal result1;
    init_decimal(&result1);

    s21_sub(dec1, dec2, &result1);
    printf("minus minus decimal\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_mul1) {
    int eq = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0b00000000000000000000000000000100;

    s21_decimal result1;
    init_decimal(&result1);

    s21_mul(dec1, dec2, &result1);
    printf("mul test\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq, 1);

} END_TEST

START_TEST(test_mul2) {
    int eq = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0b00000000000000000000000000000100;

    s21_decimal result1;
    init_decimal(&result1);

    s21_mul(dec1, dec2, &result1);
    printf("mul test\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq, 1);

} END_TEST

START_TEST(test_mul3) {
    int eq = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0b10000000000000000000000000000000;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0b00000000000000000000000000000100;

    s21_decimal result1;
    init_decimal(&result1);

    s21_mul(dec1, dec2, &result1);
    printf("mul test\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq, 1);

} END_TEST

START_TEST(test_mul4) {
    int eq = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0b10000000000000000000000000000000;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 0b00000000000000000000000000000100;

    s21_decimal result1;
    init_decimal(&result1);

    s21_mul(dec1, dec2, &result1);
    printf("mul test\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq, 1);

} END_TEST

START_TEST(test_mul5) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0b10000000000000000000000000000000;
    dec1.bits[2] = 0b10000000000000000000000000000000;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0b10000000000000000000000000000000;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal result1;
    init_decimal(&result1);

    
    ck_assert_int_eq(s21_mul(dec1, dec2, &result1), 2);

} END_TEST

START_TEST(test_mul6) {
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0b10000000000000000000000000000000;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0b10000000000000000000000000000000;
    dec2.bits[1] = 0;
    dec2.bits[0] = 0b00000000000000000000000000000010;

    s21_decimal result1;
    init_decimal(&result1);

    
    ck_assert_int_eq(s21_mul(dec1, dec2, &result1), 1);

} END_TEST

// test for div

// START_TEST(test_div1) {
//     int eq = 9;
//     s21_decimal dec1;
//     init_decimal(&dec1);
//     dec1.bits[3] = 0;
//     dec1.bits[2] = 0;
//     dec1.bits[1] = 0;
//     dec1.bits[0] = 0b00000000000000000000000000000100;

//     s21_decimal dec2;
//     init_decimal(&dec2);
//     dec2.bits[3] = 0;
//     dec2.bits[2] = 0;
//     dec2.bits[1] = 0;
//     dec2.bits[0] = 0b00000000000000000000000000000100;

//     s21_decimal result1;
//     init_decimal(&result1);

//     s21_decimal stock_result;
//     stock_result.bits[3] = 0;
//     stock_result.bits[2] = 0;
//     stock_result.bits[1] = 0;
//     stock_result.bits[0] = 0b00000000000000000000000000000001;

//     s21_div(dec1, dec2, &result1);
//     eq = s21_is_equal(stock_result, result1);
//     ck_assert_int_eq(eq, 1);

// } END_TEST

// START_TEST(test_div2) {
//     int eq = 9;
//     s21_decimal dec1;
//     init_decimal(&dec1);
//     dec1.bits[3] = 0;
//     dec1.bits[2] = 0b10000100000010001011010100111000;
//     dec1.bits[1] = 0b01000000101111001001011100110101;
//     dec1.bits[0] = 0b00011100010001011011000001001111;

//     s21_decimal dec2;
//     init_decimal(&dec2);
//     dec2.bits[3] = 0;
//     dec2.bits[2] = 0;
//     dec2.bits[1] = 0;
//     dec2.bits[0] = 0b00000000000000000000000000000011;

//     s21_decimal result1;
//     init_decimal(&result1);

//     s21_decimal stock_result;
//     stock_result.bits[3] = 0;
//     stock_result.bits[2] = 0b00101100000000101110011100010010;
//     stock_result.bits[1] = 0b11000000001111101101110100010001;
//     stock_result.bits[0] = 0b10110100000101110011101011000101;

//     s21_div(dec1, dec2, &result1);
//     eq = s21_is_equal(stock_result, result1);
//     ck_assert_int_eq(eq, 1);

// } END_TEST

// START_TEST(test_div3) {
//     int eq = 9;
//     s21_decimal dec1;
//     init_decimal(&dec1);
//     dec1.bits[3] = 0b10000000000000000000000000000000;
//     dec1.bits[2] = 0b10000100000010001011010100111000;
//     dec1.bits[1] = 0b01000000101111001001011100110101;
//     dec1.bits[0] = 0b00011100010001011011000001001111;

//     s21_decimal dec2;
//     init_decimal(&dec2);
//     dec2.bits[3] = 0;
//     dec2.bits[2] = 0;
//     dec2.bits[1] = 0;
//     dec2.bits[0] = 0b00000000000000000000000000000011;

//     s21_decimal result1;
//     init_decimal(&result1);

//     s21_decimal stock_result;
//     stock_result.bits[3] = 0b10000000000000000000000000000000;
//     stock_result.bits[2] = 0b00101100000000101110011100010010;
//     stock_result.bits[1] = 0b11000000001111101101110100010001;
//     stock_result.bits[0] = 0b10110100000101110011101011000101;

//     s21_div(dec1, dec2, &result1);
//     eq = s21_is_equal(stock_result, result1);
//     ck_assert_int_eq(eq, 1);

// } END_TEST

// START_TEST(test_div4) {
//     int eq = 9;
//     s21_decimal dec1;
//     init_decimal(&dec1);
//     dec1.bits[3] = 0;
//     dec1.bits[2] = 0b10000100000010001011010100111000;
//     dec1.bits[1] = 0b01000000101111001001011100110101;
//     dec1.bits[0] = 0b00011100010001011011000001001111;

//     s21_decimal dec2;
//     init_decimal(&dec2);
//     dec2.bits[3] = 0b10000000000000000000000000000000;
//     dec2.bits[2] = 0;
//     dec2.bits[1] = 0;
//     dec2.bits[0] = 0b00000000000000000000000000000011;

//     s21_decimal result1;
//     init_decimal(&result1);

//     s21_decimal stock_result;
//     stock_result.bits[3] = 0b10000000000000000000000000000000;
//     stock_result.bits[2] = 0b00101100000000101110011100010010;
//     stock_result.bits[1] = 0b11000000001111101101110100010001;
//     stock_result.bits[0] = 0b10110100000101110011101011000101;

//     s21_div(dec1, dec2, &result1);
//     eq = s21_is_equal(stock_result, result1);
//     ck_assert_int_eq(eq, 1);

// } END_TEST

// START_TEST(test_div5) {
//     int eq = 9;
//     s21_decimal dec1;
//     init_decimal(&dec1);
//     dec1.bits[3] = 0;
//     dec1.bits[2] = 0b10000100000010001011010100111000;
//     dec1.bits[1] = 0b01000000101111001001011100110101;
//     dec1.bits[0] = 0b00011100010001011011000001001111;

//     s21_decimal dec2;
//     init_decimal(&dec2);
//     dec2.bits[3] = 0;
//     dec2.bits[2] = 0;
//     dec2.bits[1] = 0;
//     dec2.bits[0] = 0;

//     s21_decimal result1;
//     init_decimal(&result1);

//     eq = s21_div(dec1, dec2, &result1);
//     ck_assert_int_eq(eq, 3);

// } END_TEST

// START_TEST(test_div6) {
//     int eq = 9;
//     s21_decimal dec1;
//     init_decimal(&dec1);
//     dec1.bits[3] = 0;
//     dec1.bits[2] = 0b10000100000010001011010100111000;
//     dec1.bits[1] = 0b01000000101111001001011100110101;
//     dec1.bits[0] = 0b00011100010001011011000001001111;

//     s21_decimal dec2;
//     init_decimal(&dec2);
//     dec2.bits[3] = 0;
//     dec2.bits[2] = 0;
//     dec2.bits[1] = 0;
//     dec2.bits[0] = 0b00000000000000000000000000001001;

//     setScale(1, dec2);

//     s21_decimal result1;
//     init_decimal(&result1);

//     eq = s21_div(dec1, dec2, &result1);
//     ck_assert_int_eq(eq, 1);

// } END_TEST

// START_TEST(test_div7) {
//     int eq = 9;
//     s21_decimal dec1;
//     init_decimal(&dec1);
//     dec1.bits[3] = 0b10000000000000000000000000000000;
//     dec1.bits[2] = 0b10000100000010001011010100111000;
//     dec1.bits[1] = 0b01000000101111001001011100110101;
//     dec1.bits[0] = 0b00011100010001011011000001001111;

//     s21_decimal dec2;
//     init_decimal(&dec2);
//     dec2.bits[3] = 0;
//     dec2.bits[2] = 0;
//     dec2.bits[1] = 0;
//     dec2.bits[0] = 0b00000000000000000000000000001001;

//     setScale(1, dec2);

//     printf("\n\n");

//     s21_decimal result1;
//     init_decimal(&result1);

//     eq = s21_div(dec1, dec2, &result1);
//     ck_assert_int_eq(eq, 2);

// } END_TEST


// THIS MAIN FUNCTION


int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);

    // without scale

    tcase_add_test(tc1_1, test_is_equal1);
    tcase_add_test(tc1_1, test_is_equal2);
    tcase_add_test(tc1_1, test_is_equal3);
    tcase_add_test(tc1_1, test_is_equal4);
    tcase_add_test(tc1_1, test_is_equal5);
    tcase_add_test(tc1_1, test_is_equal6);

    // without scale

    tcase_add_test(tc1_1, test_is_greater_or_equal1);
    tcase_add_test(tc1_1, test_is_greater_or_equal2);
    tcase_add_test(tc1_1, test_is_greater_or_equal3);
    tcase_add_test(tc1_1, test_is_greater_or_equal4);

    // without scale

    tcase_add_test(tc1_1, test_is_greater1);
    tcase_add_test(tc1_1, test_is_greater2);
    tcase_add_test(tc1_1, test_is_greater3);
    tcase_add_test(tc1_1, test_is_greater4);
    tcase_add_test(tc1_1, test_is_greater5);
    tcase_add_test(tc1_1, test_is_greater6);
    tcase_add_test(tc1_1, test_is_greater7);

    // without scale

    tcase_add_test(tc1_1, test_is_less_or_equal1);
    tcase_add_test(tc1_1, test_is_less_or_equal2);
    tcase_add_test(tc1_1, test_is_less_or_equal3);
    tcase_add_test(tc1_1, test_is_less_or_equal4);
    tcase_add_test(tc1_1, test_is_less_or_equal5);

    // without scale

    tcase_add_test(tc1_1, test_is_less1);
    tcase_add_test(tc1_1, test_is_less2);
    tcase_add_test(tc1_1, test_is_less3);
    tcase_add_test(tc1_1, test_is_less4);
    tcase_add_test(tc1_1, test_is_less5);
    tcase_add_test(tc1_1, test_is_less6);

    // with scale

    tcase_add_test(tc1_1, test_is_not_equal1);
    tcase_add_test(tc1_1, test_is_not_equal2);
    tcase_add_test(tc1_1, test_is_not_equal3);
    tcase_add_test(tc1_1, test_is_not_equal4);
    tcase_add_test(tc1_1, test_is_not_equal5);

    // test for add

    tcase_add_test(tc1_1, test_add1);
    tcase_add_test(tc1_1, test_add2);
    tcase_add_test(tc1_1, test_add3);
    tcase_add_test(tc1_1, test_add4);
    tcase_add_test(tc1_1, test_add44);
    tcase_add_test(tc1_1, test_add441);
    tcase_add_test(tc1_1, test_add5);
    tcase_add_test(tc1_1, test_add6);
    tcase_add_test(tc1_1, test_add7);
    tcase_add_test(tc1_1, test_add8);
    tcase_add_test(tc1_1, test_add9);
    tcase_add_test(tc1_1, test_add10);
    tcase_add_test(tc1_1, test_add11);
    tcase_add_test(tc1_1, test_add12);
    tcase_add_test(tc1_1, test_add13);
    tcase_add_test(tc1_1, test_add14);
    // tcase_add_test(tc1_1, test_add15);

    // test for sub

    tcase_add_test(tc1_1, test_sub4);
    tcase_add_test(tc1_1, test_sub5);
    tcase_add_test(tc1_1, test_sub6);
    tcase_add_test(tc1_1, test_sub7);
    tcase_add_test(tc1_1, test_sub8);
    tcase_add_test(tc1_1, test_sub9);
    tcase_add_test(tc1_1, test_sub10);
    tcase_add_test(tc1_1, test_sub11);
    tcase_add_test(tc1_1, test_sub12);
    tcase_add_test(tc1_1, test_sub13);
    tcase_add_test(tc1_1, test_sub14);


    // test for mul

    tcase_add_test(tc1_1, test_mul1);
    tcase_add_test(tc1_1, test_mul2);
    tcase_add_test(tc1_1, test_mul3);
    tcase_add_test(tc1_1, test_mul4);
    tcase_add_test(tc1_1, test_mul5);
    tcase_add_test(tc1_1, test_mul6);

    // test for div

    // tcase_add_test(tc1_1, test_div1);
    // tcase_add_test(tc1_1, test_div2);
    // tcase_add_test(tc1_1, test_div3);
    // tcase_add_test(tc1_1, test_div4);
    // tcase_add_test(tc1_1, test_div5);
    // tcase_add_test(tc1_1, test_div6);
    // tcase_add_test(tc1_1, test_div7);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
