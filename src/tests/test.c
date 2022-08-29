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
                // printf("\n");
                // printf("\n\n\n\n\ny = %d\nx = %d\n\n\n\n\n", y, x);
                // smart_print_binary_decimal(dec1);
                // smart_print_binary_decimal(dec2);
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

    // smart_print_binary_decimal(dec1);
    // printf("\n\n");
    // smart_print_binary_decimal(dec2);
    // printf("\n\n");
    // smart_print_binary_decimal(result1);
    // printf("\n\n");
    // smart_print_binary_decimal(my_result);


    ck_assert_int_eq(result1.bits[0], my_result.bits[0]);
    
} END_TEST

START_TEST(test_add2) {

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

    int eq_add = s21_is_equal(result1, my_result);

    ck_assert_int_eq(eq_add, 1);
    
} END_TEST

START_TEST(test_add3) {

    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 777;
    dec1.bits[1] = 0;
    dec1.bits[0] = 0;

    s21_decimal dec2;
    init_decimal(&dec2);  // реализация в умножении !!!
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 2;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 777;
    my_result.bits[1] = 0;
    my_result.bits[0] = 2;

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);

    int eq_add = s21_is_equal(result1, my_result);

    // smart_print_binary_decimal(dec1);
    // printf("\n\n");
    // smart_print_binary_decimal(dec2);
    // printf("\n\n");
    // smart_print_binary_decimal(dec2);
    // printf("\n\n");
    // smart_print_binary_decimal(result1);
    // printf("\n\n");
    // smart_print_binary_decimal(my_result);


    ck_assert_int_eq(eq_add, 1);
    
} END_TEST

// TEST FOR INF

START_TEST(test_add4) {

    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 4294967295;
    dec1.bits[1] = 4294967295;
    dec1.bits[0] = 4294967295;

    s21_decimal dec2;
    init_decimal(&dec2);  // реализация в умножении !!!
    dec2.bits[3] = 0;
    dec2.bits[2] = 4294967295;
    dec2.bits[1] = 4294967295;
    dec2.bits[0] = 4294967295;

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 777;
    my_result.bits[1] = 0;
    my_result.bits[0] = 2;

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);

    int eq_add = s21_is_equal(result1, my_result);

    // smart_print_binary_decimal(dec1);
    // printf("\n\n");
    // smart_print_binary_decimal(dec2);
    // printf("\n\n");
    // smart_print_binary_decimal(dec2);
    // printf("\n\n");
    // smart_print_binary_decimal(result1);
    // printf("\n\n");
    // smart_print_binary_decimal(my_result);


    ck_assert_int_eq(eq_add, 1);
    
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

    // smart_print_binary_decimal(dec1);
    // printf("\n\n");
    // smart_print_binary_decimal(dec2);
    // printf("\n\n");
    // smart_print_binary_decimal(result1);
    // printf("\n\n");
    // smart_print_binary_decimal(my_result);


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
    smart_print_binary_decimal(result1);

    int eq_add = s21_is_equal(result1, my_result);


    // printf("\n\n\n\n\n\n");
    // smart_print_binary_decimal(dec1);
    // printf("\n\n");
    // smart_print_binary_decimal(dec2);
    // printf("\n\n");
    // smart_print_binary_decimal(result1);
    // printf("\n\n");
    // smart_print_binary_decimal(my_result);


    ck_assert_int_eq(eq_add, 1);
    
} END_TEST


START_TEST(test_add7) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 2147483648;
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
    my_result.bits[3] = 2147483648;
    my_result.bits[2] = 4294967294;
    my_result.bits[1] = 1;
    my_result.bits[0] = 0;

    s21_decimal result1;
    // 11111111111111111111111111111110 00000000000000000000000000000001 00000000000000000000000000000000
    s21_add(dec1, dec2, &result1);
    eq_add = s21_is_equal(result1, my_result);

    // printf("\n\n\n\n\n\n");
    // smart_print_binary_decimal(dec1);
    // printf("\n\n");
    // smart_print_binary_decimal(dec2);
    // printf("\n\n");
    // smart_print_binary_decimal(result1);
    // printf("\n\n");
    // smart_print_binary_decimal(my_result);

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

// 000000000000000011010101000110110000000000000000001000010110111100000000000000000001111011000011
    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 2147483648;
    dec2.bits[2] = 7848488;
    dec2.bits[1] = 5455165;
    dec2.bits[0] = 111588;

// 000000000111011111000010001010000000000001010011001111010011110100000000000000011011001111100100

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 2147483648;
    my_result.bits[2] = 7793933;
    my_result.bits[1] = 5446606;
    my_result.bits[0] = 103713;

// 000000000111011011101101000011010000000001010011000110111100111000000000000000011001010100100001

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    printf("\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST

START_TEST(test_add9) {
    int eq_add = 0;
    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 54555;  
    dec1.bits[1] = 8559;  
    dec1.bits[0] = 7875;

    setScale(22, &dec1);

// 000000000000000011010101000110110000000000000000001000010110111100000000000000000001111011000011
    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 2147483648;
    dec2.bits[2] = 7848488;
    dec2.bits[1] = 5455165;
    dec2.bits[0] = 111588;

    setScale(5, &dec2);

// 000000000111011111000010001010000000000001010011001111010011110100000000000000011011001111100100

    // s21_decimal my_result;
    // init_decimal(&my_result);
    // my_result.bits[3] = 2147483648;
    // my_result.bits[2] = 7793933;
    // my_result.bits[1] = 5446606;
    // my_result.bits[0] = 103713;

// 000000000111011011101101000011010000000001010011000110111100111000000000000000011001010100100001

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    printf("\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    // smart_print_binary_decimal(my_result);
    // eq_add = s21_is_equal(result1, my_result);
    // ck_assert_int_eq(eq_add, 1);

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

// 00000000000000001101010100011011 00000000000000000010000101101111 00000000000000000001111011000011
    
    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 2147483648;
    dec2.bits[2] = 7848488;
    dec2.bits[1] = 5455165;
    dec2.bits[0] = 111588;

    setScale(22, &dec2); 

// 00000000011101111100001000101000 00000000010100110011110100111101 00000000000000011011001111100100

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 2147483648;
    my_result.bits[2] = 7903043;
    my_result.bits[1] = 5463724;
    my_result.bits[0] = 119463;

// 00000000011110001001011101000011 00000000010100110101111010101100 00000000000000011101001010100111

    s21_decimal result1;
    init_decimal(&result1);

    s21_add(dec1, dec2, &result1);
    printf("\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);
    eq_add = s21_is_equal(result1, my_result);
    ck_assert_int_eq(eq_add, 1);

} END_TEST


// Добавить скейл в сложение


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
    // tcase_add_test(tc1_1, test_add4); test for INF
    tcase_add_test(tc1_1, test_add5);
    tcase_add_test(tc1_1, test_add6);
    tcase_add_test(tc1_1, test_add7);
    tcase_add_test(tc1_1, test_add8);
    tcase_add_test(tc1_1, test_add9);
    tcase_add_test(tc1_1, test_add10);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
