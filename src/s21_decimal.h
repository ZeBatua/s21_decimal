#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    success,
    overflow,
    neg_overflow,
    invalid_scale,
} value_type_t;

typedef struct {
    int bits[4];
    value_type_t value_type;
} s21_decimal;


int getBit(int decimal, int position);
void setBit(int value_bit, int *decimal, int position);
void inversBit(int *decimal, int position);
int getScale(s21_decimal value);
void setScale(int scale, s21_decimal *value);
int getSign(s21_decimal value);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
void init_decimal(s21_decimal *decimal);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_negate(s21_decimal value, s21_decimal *result);
void equate_decimal(s21_decimal basic, s21_decimal *decimal);
int get_decimal_bit(s21_decimal decimal, int position);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
void compare_scale (s21_decimal *first, s21_decimal *secod);
void decimal_to_binary_mass(s21_decimal decimal, int *mass);
void multiply_by_ten(s21_decimal *decimal);
void set_decimal_bit(s21_decimal *decimal, int bait, int position, int value);
void alt_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void equate_scale(s21_decimal *first_value, s21_decimal *second_value);
int s21_truncate(s21_decimal value, s21_decimal *result);
void shift_left(s21_decimal *x2_dec, int time);
void shift_right(s21_decimal *x2_dec, int time);
void alt_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);


// char get_int_bit(int number, int position);
// char get_decimal_bit(s21_decimal decimal, int position);
// void equate_decimal(s21_decimal basic, s21_decimal *decimal);
// void set_int_bit(int *number, int position, int bit_value);
// char add_int(int value_1, int value_2, int *result, int transfer);

// int change_bit(int number, int index);

#endif  // SRC_S21_DECIMAL_H_
