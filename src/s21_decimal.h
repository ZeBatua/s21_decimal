#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <string.h>

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

typedef struct {
    int extBits[10];
    value_type_t value_type;
} s21_extended_decimal;


int getBit(int value, int position);
void setBit(int value_bit, int *decimal, int position);
void inversBit(int *decimal, int position);
int getScale(s21_decimal value);
void setScale(int scale, s21_decimal *value);
int getSign(s21_decimal value);
void setSign(s21_decimal *value, int sign);

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
int alt_add(s21_extended_decimal value_1, s21_extended_decimal value_2, s21_extended_decimal *result);
// int equate_scale(s21_decimal *first_value, s21_decimal *second_value);
int s21_truncate(s21_decimal value, s21_decimal *result);
void shift_left(s21_extended_decimal *x2_dec, int time);
void shift_right(s21_extended_decimal *decimal, int time);
void alt_sub(s21_extended_decimal value_1, s21_extended_decimal value_2, s21_extended_decimal *result);
void division_by_ten(s21_extended_decimal *decimal);
void print_binary_decimal(int mass[]);
void smart_print_binary_decimal(s21_decimal dec);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int is_less_no_sign(s21_extended_decimal value_1, s21_extended_decimal value_2);
void subtraction_no_sign(s21_extended_decimal value_1, s21_extended_decimal value_2, s21_extended_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void create_mask(s21_extended_decimal ext_value_1, s21_extended_decimal ext_value_2, s21_extended_decimal *first_dec_mask, s21_extended_decimal *second_dec_mask, int *shift_counter, int bit);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int is_equal_no_sign(s21_extended_decimal value_1, s21_extended_decimal value_2);

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_floor(s21_decimal value, s21_decimal *result);

int add_no_equote(s21_extended_decimal value_1, s21_extended_decimal value_2, s21_extended_decimal *result);
int sub_no_equote(s21_extended_decimal value_1, s21_extended_decimal value_2, s21_extended_decimal *result);

int s21_from_decimal_to_int(s21_decimal src, int *dst);

int s21_from_float_to_decimal(float src, s21_decimal *dst);
int getBinaryExp(float value);
int get_float_bit(float float_value, unsigned int *mask);

int s21_from_decimal_to_float(s21_decimal src, float *dst);



void decimal_to_string(s21_decimal decimal, char *str);
void string_to_decimal(const char *str, s21_decimal *decimal);

//--------------------extended_decimal_functions--------------------//

void init_extended_decimal(s21_extended_decimal *decimal);
int  equate_extdec_to_dec(s21_extended_decimal E_decimal, s21_decimal *decimal);
void equate_dec_to_extdec(s21_decimal basic, s21_extended_decimal *E_decimal);
int get_extdec_bit(s21_extended_decimal E_decimal, int position);
void set_extdec_bit(s21_extended_decimal *E_decimal, int bait, int position, int value);
int getExtSign(s21_extended_decimal value);
void setExtSign(s21_extended_decimal *value, int sign);
int getExtScale(s21_extended_decimal value);
void setExtScale(int scale, s21_extended_decimal *value);
int get_first_non_zero_extBit(s21_extended_decimal dec);
int equate_ext_scale(s21_extended_decimal *first_value, s21_extended_decimal *second_value);
void equate_extdec(s21_extended_decimal basic, s21_extended_decimal *E_decimal);
void multiply_extdec_by_ten(s21_extended_decimal *E_decimal);
int ext_is_less(s21_extended_decimal value_1, s21_extended_decimal value_2);
void smart_print_exdec(s21_extended_decimal dec);
void extdec_to_binary_mass(s21_extended_decimal decimal, int *mass);
void print_binary_extdec(int mass[]);



#endif  // SRC_S21_DECIMAL_H_
