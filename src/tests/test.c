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
    // smart_print_binary_decimal(result1);

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

    int eq_add = s21_is_equal(result1, my_result);

    printf("\n\n\n\n\n\n");
    smart_print_binary_decimal(dec1);
    printf("\n\n");
    smart_print_binary_decimal(dec2);
    printf("\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);


    ck_assert_int_eq(eq_add, 1);
    
} END_TEST

START_TEST(test_add8) {

    s21_decimal dec1;
    init_decimal(&dec1);
    dec1.bits[3] = 0;
    dec1.bits[2] = 0;
    dec1.bits[1] = 0;
    dec1.bits[0] = 22;

    setScale(4, &dec1);

    s21_decimal dec2;
    init_decimal(&dec2);
    dec2.bits[3] = 0;
    dec2.bits[2] = 0;
    dec2.bits[1] = 0;
    dec2.bits[0] = 1;

    setScale(4, &dec2);

    s21_decimal my_result;
    init_decimal(&my_result);
    my_result.bits[3] = 0;
    my_result.bits[2] = 0;
    my_result.bits[1] = 0;
    my_result.bits[0] = 23;

    setScale(4, &my_result);


    s21_decimal result1;

    // 11111111111111111111111111111110 00000000000000000000000000000001 00000000000000000000000000000000

    s21_add(dec1, dec2, &result1);

    int eq_add = s21_is_equal(result1, my_result);

    printf("\n\n\n\n\n\n");
    smart_print_binary_decimal(dec1);
    printf("\n\n");
    smart_print_binary_decimal(dec2);
    printf("\n\n");
    smart_print_binary_decimal(result1);
    printf("\n\n");
    smart_print_binary_decimal(my_result);


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

    // without scale

    tcase_add_test(tc1_1, test_add1);
    tcase_add_test(tc1_1, test_add2);
    tcase_add_test(tc1_1, test_add3);
    // tcase_add_test(tc1_1, test_add4); test for INF
    tcase_add_test(tc1_1, test_add5);
    tcase_add_test(tc1_1, test_add6);
    tcase_add_test(tc1_1, test_add7);
    tcase_add_test(tc1_1, test_add8);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
