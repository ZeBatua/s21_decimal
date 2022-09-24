#include "../../s21_decimal.h"

int s21_round(s21_decimal value,
              s21_decimal *result) {  // эту функцию не было смысла переводить в
                                      // extec так как нет equate_scale
  int error = 0;

  s21_extended_decimal ext_buf, ext_one, ext_value, ext_result;
  init_extended_decimal(&ext_buf);
  init_extended_decimal(&ext_one);
  init_extended_decimal(&ext_value);
  init_extended_decimal(&ext_result);

  s21_decimal buf, remainder, five;
  init_decimal(&buf);
  init_decimal(&remainder);
  init_decimal(&five);

  five.bits[0] = 5;
  ext_one.extBits[0] = 1;

  equate_dec_to_extdec(value, &ext_value);

  equate_extdec(ext_value, &ext_buf);
  while (getScale(value) > 0) {
    division_by_ten(&ext_buf);         // scale -1
    multiply_extdec_by_ten(&ext_buf);  // scale +1

    int save_scale_2 = getExtScale(ext_buf);

    equate_extdec_to_dec(ext_value, &value);
    equate_extdec_to_dec(ext_buf, &buf);

    s21_sub(value, buf, &remainder);

    setScale(save_scale_2, &remainder);
    setSign(&remainder, 0);
    setScale(save_scale_2, &five);
    setSign(&five, 0);

    if (s21_is_greater_or_equal(remainder, five)) {  // требует версии для extdec
      division_by_ten(&ext_buf);

      int save_scale = getExtScale(ext_buf);
      int save_sign = getExtSign(ext_buf);

      equate_dec_to_extdec(value, &ext_value);
      setExtSign(&ext_one, getExtSign(ext_buf));
      add_no_equote(ext_buf, ext_one, &ext_value);

      equate_extdec_to_dec(ext_value, &value);

      setScale(save_scale, &value);
      setSign(&value, save_sign);
    } else {
      division_by_ten(&ext_buf);
      equate_extdec_to_dec(ext_buf, &value);
    }
  }
  equate_decimal(value, result);
  return error;
}
// округление до ближайшего целого числа