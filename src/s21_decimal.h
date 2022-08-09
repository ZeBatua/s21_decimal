#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>

typedef enum {
    success,
    overflow,
    neg_overflow,
    invalid_scale,
} value_type_t;

typedef struct {
    int bits[3];
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

// char get_int_bit(int number, int position);
// char get_decimal_bit(s21_decimal decimal, int position);
// void equate_decimal(s21_decimal basic, s21_decimal *decimal);
// void set_int_bit(int *number, int position, int bit_value);
// char add_int(int value_1, int value_2, int *result, int transfer);

// int change_bit(int number, int index);

#endif  // SRC_S21_DECIMAL_H_
