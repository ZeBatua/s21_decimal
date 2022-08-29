#include "../../s21_decimal.h"


int s21_round(s21_decimal value, s21_decimal *result) { // эту функцию не было смысла переводить в extec так как нет equate_scale
    int error = 0;
    s21_extended_decimal ext_buf, ext_one, ext_value, ext_result;
    init_extended_decimal(&ext_buf);
    init_extended_decimal(&ext_one);
    s21_decimal buf, remainder, five;
    init_decimal(&buf);
    init_decimal(&remainder);
    five.bits[0] = 5;
    ext_one.extBits[0] = 1;
    equate_extdec(ext_value, &ext_buf);
    while (getScale(value) > 0) {
        division_by_ten(&ext_buf); // scale -1
        multiply_extdec_by_ten(&ext_buf); // scale +1

        int save_scale_2 = getExtScale(ext_buf);
        int save_sign_2 = getExtSign(ext_buf);


        equate_extdec_to_dec(ext_value, &value);
        equate_extdec_to_dec(ext_buf, &buf);

        s21_sub(value, buf, &remainder); // тут может быть ошибка поэтому возможно лучше создать ext_add


        setScale(save_scale_2, &remainder);
        setSign(&remainder, save_sign_2);
        setScale(save_scale_2, &five);
        setSign(&five, save_sign_2);

        if (s21_is_greater_or_equal(remainder, five)) { // требует версии для extdec
            division_by_ten(&ext_buf);

            int save_scale = getExtScale(ext_buf);
            int save_sign = getExtSign(ext_buf);

            equate_dec_to_extdec(value, &ext_value);
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