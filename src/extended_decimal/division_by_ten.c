#include "../s21_decimal.h"

int division_by_ten(s21_extended_decimal *decimal) {
  s21_extended_decimal dec_for_get_remainder;
  equate_extdec(*decimal, &dec_for_get_remainder);

  int save_scale = getExtScale(*decimal);
  int save_sign = getExtSign(*decimal);
  //-----1-----//
  s21_extended_decimal dec_buf1, dec_buf2, qwe;
  init_extended_decimal(&dec_buf1);
  init_extended_decimal(&dec_buf2);
  init_extended_decimal(&qwe);
  equate_extdec(*decimal, &dec_buf1);
  equate_extdec(*decimal, &dec_buf2);

  shift_right(&dec_buf1, 1);
  shift_right(&dec_buf2, 2);
  add_no_equote(dec_buf1, dec_buf2, &qwe);

  //-----2-----//
  s21_extended_decimal buf_qwe;
  init_extended_decimal(&buf_qwe);
  equate_extdec(qwe, &buf_qwe);
  shift_right(&qwe, 4);
  add_no_equote(buf_qwe, qwe, &qwe);

  //-----3-----//
  equate_extdec(qwe, &buf_qwe);
  shift_right(&qwe, 8);
  add_no_equote(buf_qwe, qwe, &qwe);

  //-----4-----//
  equate_extdec(qwe, &buf_qwe);
  shift_right(&qwe, 16);
  add_no_equote(buf_qwe, qwe, &qwe);

  equate_extdec(qwe, &buf_qwe);
  shift_right(&qwe, 32);
  add_no_equote(buf_qwe, qwe, &qwe);

  equate_extdec(qwe, &buf_qwe);
  shift_right(&qwe, 64);
  add_no_equote(buf_qwe, qwe, &qwe);

  equate_extdec(qwe, &buf_qwe);
  shift_right(&qwe, 128);
  add_no_equote(buf_qwe, qwe, &qwe);

  equate_extdec(qwe, &buf_qwe);
  shift_right(&qwe, 256);
  add_no_equote(buf_qwe, qwe, &qwe);

  //-----5-----//
  shift_right(&qwe, 3);

  //-----6-----//
  s21_extended_decimal res;
  init_extended_decimal(&res);
  equate_extdec(qwe, &buf_qwe);

  shift_left(&buf_qwe, 2);
  add_no_equote(buf_qwe, qwe, &buf_qwe);
  shift_left(&buf_qwe, 1);
  equate_extdec(*decimal, &dec_buf1);
  sub_no_equote(dec_buf1, buf_qwe, &res);

  //-----7-----//
  if (res.extBits[0] > 9 || res.extBits[1] > 0 || res.extBits[2] > 0 ||
      res.extBits[3] > 0 || res.extBits[4] > 0 || res.extBits[5] > 0 ||
      res.extBits[6] > 0 || res.extBits[7] > 0 || res.extBits[8] > 0) {
    init_extended_decimal(&res);
    res.extBits[0] = 1;
    setExtSign(&res, getExtSign(qwe));
    add_no_equote(res, qwe, &qwe);
    equate_extdec(qwe, decimal);
  } else {
    equate_extdec(qwe, decimal);
  }
  setExtScale(save_scale, decimal);
  setExtSign(decimal, save_sign);
  if (getExtScale(*decimal) > 0) {
    setExtScale(getExtScale(*decimal) - 1, decimal);
  }

  //------------------------------------get_remainder-------------------------------------------//

  s21_extended_decimal remainder, x10_decimal;
  init_extended_decimal(&remainder);
  init_extended_decimal(&x10_decimal);
  equate_extdec(*decimal, &x10_decimal);

  multiply_extdec_by_ten(&x10_decimal);

  sub_no_equote(dec_for_get_remainder, x10_decimal,
                &remainder);  // result это число от 0 до 9

  int int_remainder = 0;
  int_remainder = remainder.extBits[0];

  return int_remainder;
}
