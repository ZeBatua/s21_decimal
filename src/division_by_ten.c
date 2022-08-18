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

    smart_print_binary_decimal(qwe);
    printf(" q = (n >> 1) + (n >> 2)\n\n");
    //-----2-----//
    s21_decimal buf_qwe;
    init_decimal(&buf_qwe);
    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 4);
    alt_add(buf_qwe, qwe, &qwe);

    printf(" 4desiatichnaia zapis = %d\n", qwe.bits[0]);
    smart_print_binary_decimal(qwe);
    printf(" q = q + (q >> 4)\n\n");
    //-----3-----//
    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 8);
    alt_add(buf_qwe, qwe, &qwe);

    printf(" 8desiatichnaia zapis = %d\n\n", qwe.bits[0]);
    smart_print_binary_decimal(qwe);
    printf(" ALArM BLIA q = q + (q >> 8)\n decimal = %d\n\n", qwe.bits[0]);
    //-----4-----//
    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 16);
    alt_add(buf_qwe, qwe, &qwe);

    smart_print_binary_decimal(qwe);
    printf(" q = q + (q >> 16)\n\n");

    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 32);
    alt_add(buf_qwe, qwe, &qwe);

    smart_print_binary_decimal(qwe);
    printf(" q = q + (q >> 32)\n\n");

    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 64);
    alt_add(buf_qwe, qwe, &qwe);
    
    smart_print_binary_decimal(qwe);
    printf(" q = q + (q >> 64)\n\n");
    //-----5-----//
    shift_right(&qwe, 3);

    smart_print_binary_decimal(qwe);
    printf(" q = q >> 3\n\n");
    //-----6-----//
    s21_decimal res;
    init_decimal(&res);
    equate_decimal(qwe, &buf_qwe);
    shift_left(&buf_qwe, 2); // здесь по идее я должен в любом случае сделать шифт
    alt_add(buf_qwe, qwe, &buf_qwe);
    shift_left(&buf_qwe, 1);
    equate_decimal(*decimal, &dec_buf1);
    alt_sub(dec_buf1, buf_qwe, &res);

    smart_print_binary_decimal(res);
    printf(" r = n - (((q << 2) + q) << 1)\n r = %d\n", res.bits[0]);
    
    //-----7-----//
    if (res.bits[0] > 9 || res.bits[1] > 0 || res.bits[2] > 0) {
        printf("get in if\n");
        init_decimal(&res);
        res.bits[0] = 1;
        alt_add(res, qwe, &qwe);
        smart_print_binary_decimal(qwe);
        equate_decimal(qwe, decimal);
    } else {
        equate_decimal(qwe, decimal);
        smart_print_binary_decimal(qwe);
    }

}
