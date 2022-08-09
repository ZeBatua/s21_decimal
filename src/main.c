#include "s21_decimal.h"

int main() {
    s21_decimal test_scale;
    s21_decimal dst;
    test_scale.bits[3] = 0;
    dst.bits[3] = 0;
    int src = -102000;
    s21_decimal result;

    printf("scale = %d\n", getScale(test_scale));
    setScale(5, &test_scale);
    printf("scale = %d\n", getScale(test_scale));
    getSign(test_scale);
    printf("sign = %d\n", getSign(test_scale));

    s21_from_int_to_decimal(src, &dst);
    printf("decimal = %d\n", dst);
    printf("sign = %d\n", getSign(dst));
    s21_negate(dst, &result);
    printf("sign after negate = %d\n", getSign(dst)); // пока не отрабатывает знак
    return 0;
}


// int s21_from_decimal_to_int(s21_decimal src, int *dst) {
//     int position = 0;
//     int error = 0;
//     if (dst) {
//         init_decimal(&src);
//         position = getScale(src);
//         src >> position;
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
    equate_decimal(value, result); // эта функция записывает value в result
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

int getScale(s21_decimal value) {
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
void setBit(int value_bit, int *decimal, int position) {
    int mask = 1;
    if (getBit(*decimal, position) != value_bit) {
        mask = mask << position;
        *decimal ^= mask;    
    }
}

int getBit(int decimal, int position) {
    char result = 0;
    decimal = decimal >> position;
    if (decimal & 1 == 1) {
        result = 1;
    } 
    return result;
}

// void print_decimal() {
