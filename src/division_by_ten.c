#include "s21_decimal.h"

void division_by_ten(s21_decimal *decimal) {
    //-----1-----//
    s21_decimal dec_buf1, dec_buf2, qwe;
    init_decimal(&dec_buf1);
    init_decimal(&dec_buf2);
    init_decimal(&qwe);
    equate_decimal(*decimal, &dec_buf1);
    equate_decimal(*decimal, &dec_buf2);

    shift_right(&dec_buf1, 1);
    shift_right(&dec_buf2, 2);
    alt_add(dec_buf1, dec_buf2, &qwe);

    // int mass1[128] = {0};
    // decimal_to_binary_mass(qwe, mass1);
    // for (int i = 127; i >= 0; i--) {
    //     if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //         printf(" ");
    //     }
    //     printf("%d", mass1[i]);
    // }
    // printf("\n q = (n >> 1) + (n >> 2)\n");
    // //-----2-----//
    s21_decimal buf_qwe;
    init_decimal(&buf_qwe);
    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 4);
    alt_add(buf_qwe, qwe, &qwe);

    // int mass2[128] = {0};
    // decimal_to_binary_mass(qwe, mass2);
    // for (int i = 127; i >= 0; i--) {
    //     if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //         printf(" ");
    //     }
    //     printf("%d", mass2[i]);
    // }
    // printf("\n q = q + (q >> 4)\n");
    //-----3-----//
    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 8);
    alt_add(buf_qwe, qwe, &qwe);

    // int mass3[128] = {0};
    // decimal_to_binary_mass(qwe, mass3);
    // for (int i = 127; i >= 0; i--) {
    //     if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //         printf(" ");
    //     }
    //     printf("%d", mass3[i]);
    // }
    // printf("\n q = q + (q >> 8)\n");
    //-----4-----//
    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 16);
    alt_add(buf_qwe, qwe, &qwe);

    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 32);
    alt_add(buf_qwe, qwe, &qwe);

    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 64);
    alt_add(buf_qwe, qwe, &qwe);
    
    // int mass4[128] = {0};
    // decimal_to_binary_mass(qwe, mass4);
    // for (int i = 127; i >= 0; i--) {
    //     if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //         printf(" ");
    //     }
    //     printf("%d", mass4[i]);
    // }
    // printf("\n q = q + (q >> 16)\n");
    //-----5-----//
    shift_right(&qwe, 3);

    // int mass5[128] = {0};
    // decimal_to_binary_mass(qwe, mass5);
    // for (int i = 127; i >= 0; i--) {
    //     if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //         printf(" ");
    //     }
    //     printf("%d", mass5[i]);
    // }
    // printf("\n q = q >> 3\n");
    //-----6-----//
    s21_decimal res;
    init_decimal(&res);
    equate_decimal(qwe, &buf_qwe);
    shift_left(&buf_qwe, 2); // здесь по идее я должен в любом случае сделать шифт
    alt_add(buf_qwe, qwe, &buf_qwe);
    shift_left(&buf_qwe, 1);
    equate_decimal(*decimal, &dec_buf1);
    
    printf("decimal - %d\n", buf_qwe.bits[0]);
    printf("sam decimal - %d\n", dec_buf1.bits[0]);
    printf("raznica = %d\n ", buf_qwe.bits[0] - dec_buf1.bits[0]);



    alt_sub(dec_buf1, buf_qwe, &res);
    
    printf("1 = %d\n", dec_buf1.bits[0]);
    printf("2 = %d\n", buf_qwe.bits[0]);
    printf("3 = %d\n", res.bits[0]);
    printf("start\n");
    int mass01[128] = {0};
    decimal_to_binary_mass(dec_buf1, mass01);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass01[i]);
    }
    printf("\nlow\n");

    int mass02[128] = {0};
    decimal_to_binary_mass(buf_qwe, mass02);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass02[i]);
    }
    printf("\nminus\n");

    int mass6[128] = {0};
    decimal_to_binary_mass(res, mass6);
    for (int i = 127; i >= 0; i--) {
        if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
            printf(" ");
        }
        printf("%d", mass6[i]);
    }
    printf("\n r = n - (((q << 2) + q) << 1)\n");
    //-----7-----//
    if (res.bits[0] > 9 || res.bits[1] > 0 || res.bits[2] > 0) {
        alt_add(res, qwe, &qwe);
    //     //------
    //     int mass6[128] = {0};
    //     decimal_to_binary_mass(qwe, mass6);
    //     for (int i = 127; i >= 0; i--) {
    //         if ((i + 1) % 32 == 0 && ((i + 1) != 0 && (i + 1) != 128)) {
    //             printf(" ");
    //         }
    //         printf("%d", mass6[i]);
    //     }
    //     printf("\n q = q + (r > 9)\n");
    //     //------
    } 
    equate_decimal(qwe, decimal);
}
