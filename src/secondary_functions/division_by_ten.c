#include "../s21_decimal.h"

void division_by_ten(s21_decimal *decimal) {
    int save_scale = getScale(*decimal);
    int save_sign = getSign(*decimal);
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

    //-----2-----//
    s21_decimal buf_qwe;
    init_decimal(&buf_qwe);
    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 4);
    alt_add(buf_qwe, qwe, &qwe);

    //-----3-----//
    equate_decimal(qwe, &buf_qwe);
    shift_right(&qwe, 8);
    alt_add(buf_qwe, qwe, &qwe);

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

    //-----5-----//
    shift_right(&qwe, 3);

    //-----6-----//
    s21_decimal res;
    init_decimal(&res);
    equate_decimal(qwe, &buf_qwe);

    shift_left(&buf_qwe, 2);
    alt_add(buf_qwe, qwe, &buf_qwe);
    shift_left(&buf_qwe, 1);
    equate_decimal(*decimal, &dec_buf1);
    alt_sub(dec_buf1, buf_qwe, &res);

    //-----7-----//
    if (res.bits[0] > 9 || res.bits[1] > 0 || res.bits[2] > 0) {
        init_decimal(&res);
        res.bits[0] = 1;
        alt_add(res, qwe, &qwe);
        equate_decimal(qwe, decimal);
    } else {
        equate_decimal(qwe, decimal);
    }
    setScale(save_scale, decimal);
    setSign(decimal, save_sign);
    if (getScale(*decimal) > 0) {
        setScale(getScale(*decimal) - 1, decimal);
    }
}
