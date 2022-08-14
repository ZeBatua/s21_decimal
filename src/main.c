#include "s21_decimal.h"

int main() {
    s21_decimal result;
    init_decimal(&result);
    //for_negative.bits[3] = -2147483648;
    result.bits[3] = pow(2, 5) + pow(2, 14);
    result.bits[2] = pow(2, 5) + pow(2, 14);
    result.bits[1] = 90;
    result.bits[0] = 1;
    int mass3[128] = {0};
    printf("scale %d\n", getScale(result));
    decimal_to_binary_mass(result, mass3);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass3[i]);
    }
    printf("\n");

    multiply_scale(&result, 1);
    int massr[128] = {0};
    decimal_to_binary_mass(result, massr);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", massr[i]);
    }
    printf("\n");
    printf("0 = %d\n", result.bits[0]);
    printf("1 = %d\n", result.bits[1]);
    printf("2 = %d\n", result.bits[2]);
    printf("3 = %d\n", result.bits[3]);
    printf("scale new %d\n", getScale(result));
    return 0;
}

void multiply_scale(s21_decimal *decimal, int delta_scale) {
    s21_decimal x2_dec, x8_dec;
    init_decimal(&x2_dec);
    init_decimal(&x8_dec);
    equate_decimal(*decimal, &x2_dec);
    equate_decimal(*decimal, &x8_dec);
    int dec_bit = 0;
    if (get_decimal_bit(x2_dec, 95) != 1) {
        for (int i = 95; i >= 0; i--) {
            if (i != 0) {
                dec_bit = get_decimal_bit(x2_dec, i - 1);
            }
            if (i == 0) {
                set_decimal_bit(&x2_dec, 0, 0, 0);
            } else {
                set_decimal_bit(&x2_dec, i / 32, i, dec_bit);
            }
        }
    }
    printf("\n");
    // --------
    int mass2[128] = {0};
    decimal_to_binary_mass(x2_dec, mass2);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass2[i]);
    }
    // --------
    // printf("0 = %d\n", result.bits[0]);
    // printf("1 = %d\n", result.bits[1]);
    // printf("2 = %d\n", result.bits[2]);
    // printf("3 = %d\n", result.bits[3]);

    int loop_counter = 0;
    if (get_decimal_bit(x8_dec, 95) != 1) { // условия
        for (int i = 95; i >= 0; i--) {
            if (i != 0) {
                dec_bit = get_decimal_bit(x8_dec, i - 1);
            }
            if (i == 0) {
                set_decimal_bit(&x8_dec, 0, 0, 0);
            } else {
                set_decimal_bit(&x8_dec, i / 32, i, dec_bit);
            }
            if (i == 0 && loop_counter < 2) {
                i = 95;
                loop_counter++;
            }
        }
    }


    printf("\n");

    // --------
    int massq[128] = {0};
    decimal_to_binary_mass(x8_dec, massq);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", massq[i]);
    }
    printf("\nsumma\n");
    s21_decimal result;
    init_decimal(&result);
    add(x2_dec, x8_dec, &result);
    ///---------
    int massr[128] = {0};
    decimal_to_binary_mass(result, massr);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", massr[i]);
    }
    printf("\n");

    equate_decimal(result, decimal);
    setScale(getScale(*decimal) + 1, decimal);
}

void add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    init_decimal(result);
    int first_dec_bit = 0, second_dec_bit = 0;
    int dec1_sign = getSign(value_1), dec2_sign = getSign(value_2);
    int over_bit = 0;
    for (int i = 0; i < 96; i++) {
        first_dec_bit = get_decimal_bit(value_1, i);
        second_dec_bit =  get_decimal_bit(value_2, i);
        if (over_bit == 0) {
            if (first_dec_bit == 1 && second_dec_bit == 0 ||
                first_dec_bit == 0 && second_dec_bit == 1) {
                set_decimal_bit(result, i / 32, i, 1);
            } else if (first_dec_bit == 0 && second_dec_bit == 0) {
                set_decimal_bit(result, i / 32, i, 0);
            } else if (first_dec_bit == 1 && second_dec_bit == 1) {
                set_decimal_bit(result, i / 32, i, 0);
                over_bit = 1;
            }
        } else if (first_dec_bit == 1 && second_dec_bit == 0 ||
            first_dec_bit == 0 && second_dec_bit == 1) {
            set_decimal_bit(result, i / 32, i, 0);
            over_bit = 1;
        } else if (first_dec_bit == 0 && second_dec_bit == 0) {
            set_decimal_bit(result, i / 32, i, 1);
            over_bit = 0;
        } else if (first_dec_bit == 1 && second_dec_bit == 1) {
            set_decimal_bit(result, i / 32, i, 1);
            over_bit = 1;
            if (i == 95) {
                fprintf(stderr, "ti perepolnilsia\n");
            }
        }
    }
}

int get_decimal_bit(s21_decimal decimal, int position) { // мб чар
    int res = 0;
    res = getBit(decimal.bits[position / 32], position % 32);
    return res;
}

void set_decimal_bit(s21_decimal *decimal, int bait, int position, int value) { // мб чар
    int a = pow(2, position % 32);
    if (value == 1) {
        if (get_decimal_bit(*decimal, position) == 0) {
            decimal->bits[bait] += a;
        }
    }  else if (value == 0) {
        if (get_decimal_bit(*decimal, position) == 1) {
            decimal->bits[bait] -= a;
        }
    }
}

int getBit(int decimal, int position) {
    int result = 0;
    decimal = decimal >> position;
    if (decimal & 1) {
        result = 1;
    } 
    return result;
}

void setBit(int value_bit, int *decimal, int position) {
    int mask = 1;
    if (getBit(*decimal, position) != value_bit) {
        mask = mask << position;
        *decimal ^= mask;    
    }
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) { // compar_scale нужен
    int result = 0;
    int first_sign = getSign(value_1);
    int second_sign = getSign(value_2);
    int bit_v1 = 0;
    int bit_v2 = 0;
    if (first_sign > second_sign) {
        result = 1;
    } else if (first_sign < second_sign) {
        result = 0;
    } else {
        for (int i = 96; i > 0; i--) {
            bit_v1 = get_decimal_bit(value_1, i);
            bit_v2 = get_decimal_bit(value_2, i);
            if (bit_v1 > bit_v2) {
                result = 0;
            } else if (bit_v2 > bit_v1) {
                result = 1;
            }
        }
    }
    return 0;
}

// void compare_scale(s21_decimal *first, s21_decimal *secod) {
//     int first_position = 0;
//     int second_position = 0;
//     int priority_position = 0;
//     first_position = find_first_non_zero_bit(); // вернет позицию первой 1-цы
//     second_position = find_first_non_zero_bit();
//     if ()
//     int difference = 0;
//     difference = scale_difference(getScale(first), getScale(second));
// }

// функция перевода decimal в массив двоичных значений

void decimal_to_binary_mass(s21_decimal decimal, int *mass) { // этой функции нужен массив в который будет записываться двоичный вид
    // if (get_decimal_bit(decimal, 128) == (1 || 0)) {
    //     exit(2); // № ошибки 
    // }
    for (int i = 0; i < 128; i++) {
        mass[i] = get_decimal_bit(decimal, i);
    }
}

void binary_result_to_decimal(s21_decimal *decimal, int mass) {
}



// int s21_from_decimal_to_int(s21_decimal src, int *dst) { // умножение, остаток деления,
//     int position = 0;
//     int error = 0;
//     if (dst) {
//         init_decimal(&src);
//         position = getScale(src);
//         src >> position;  // децимал нельзя побитово двигать 
//         dst.bits[0] = src;
//         if (getBit(src.bits[3], 31)) {
//             *dst *= -1; 
//         }
//     } else {
//         error = 1;
//     }
// }

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int error = 0;

    if (dst) {
        init_decimal(dst);
        if (src < 0) {
            setBit(1, &dst->bits[3], 31);
            printf("znak = %d\n", getBit(dst->bits[3], 31));
            src *= -1;
        }
        dst->bits[0] = src;
    } else {
        error = 1;
    }
    return error;
}


int s21_negate(s21_decimal value, s21_decimal *result) {
    int mask = -2147483648;

    init_decimal(result);
    equate_decimal(value, result); // эта функция записывает value в result FFFFFFFFFFFFFFF ГДЕ & 
    result->bits[3] ^= mask;
    return 0;
}

void equate_decimal(s21_decimal basic, s21_decimal *decimal) {
    init_decimal(decimal);
    for (int i = 0; i < 4; ++i) {
        decimal->bits[i] = basic.bits[i];
    }
}

void init_decimal(s21_decimal *decimal) {
    decimal->bits[0] = 0;
    decimal->bits[1] = 0;
    decimal->bits[2] = 0;
    decimal->bits[3] = 0;
}

void setScale(int scale, s21_decimal *value) {
    if (0 <= scale && scale <= 28) {
        for (int i = 16; i <= 23; i++) {
            int mask = pow(2, i - 16);
            if (scale & mask) {
                setBit(1, &value->bits[3], i);
            } else {
                setBit(0, &value->bits[3], i);
            }
        }
    }
}

int getScale(s21_decimal value) { // нет проверки на неадекватный scale
    int scale = 0;
    for (int i = 7; i >= 0; --i) {
        if (getBit(value.bits[3], 16 + i) == 1) {
            scale += pow(2, i);
        }
    }
    return scale;
}

int getSign(s21_decimal value) { 
    return getBit(value.bits[3], 31); 
}

void inversBit(int *decimal, int position) {
    int mask = 1;
    mask = mask << position;
    *decimal ^= mask;  
}



// void print_decimal() {
