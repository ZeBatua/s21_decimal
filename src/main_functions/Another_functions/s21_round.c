#include "../../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    int error = 0;
    s21_decimal buf, five, one, remainder;
    init_decimal(&buf);
    init_decimal(&remainder);
    init_decimal(&five);
    init_decimal(&one);
    five.bits[0] = 5;
    one.bits[0] = 1;
    equate_decimal(value, &buf);
    while (getScale(value) > 0) {
        division_by_ten(&buf); // scale -1
        int a =  getScale(buf);
        multiply_by_ten(&buf); // scale +1
        int b = getScale(buf);
        int save_scale_2 = getScale(buf);
        int save_sign_2 = getSign(buf);
        s21_sub(value, buf, &remainder);
        setScale(save_scale_2, &remainder);
        setSign(&remainder, save_sign_2);
        setScale(save_scale_2, &five);
        setSign(&five, save_sign_2);
        if (s21_is_greater_or_equal(remainder, five)) {
            division_by_ten(&buf);
            int save_scale = getScale(buf);
            int save_sign = getSign(buf);
            add_no_equote(buf, one, &value);
            setScale(save_scale, &value);
            setSign(&value, save_sign);
        } else {
            division_by_ten(&buf);
            // setScale(getScale(value) + 1, &value);
            equate_decimal(buf, &value);
        }
        
    }
    equate_decimal(value, result);
    return error;
}
// округление до ближайшего целого числа 