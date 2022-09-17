#include "../../s21_decimal.h"

int add_no_equote(s21_extended_decimal ext_value_1, s21_extended_decimal ext_value_2, s21_extended_decimal *ext_result) { // бесполезный ерор
    int error = 0;
    init_extended_decimal(ext_result);
    int first_extdec_bit = 0, second_extdec_bit = 0;
    int dec1_sign = getExtSign(ext_value_1), dec2_sign = getExtSign(ext_value_2);
    int over_bit = 0;

    if (dec1_sign == dec2_sign) {
        for (int i = 0; i < 288; i++) {
            first_extdec_bit = get_extdec_bit(ext_value_1, i);
            second_extdec_bit =  get_extdec_bit(ext_value_2, i);
            if (over_bit == 0) {
                if (first_extdec_bit == 1 && second_extdec_bit == 0 ||
                    first_extdec_bit == 0 && second_extdec_bit == 1) {
                    set_extdec_bit(ext_result, i / 32, i, 1); 
                } else if (first_extdec_bit == 0 && second_extdec_bit == 0) {
                    set_extdec_bit(ext_result, i / 32, i, 0);
                } else if (first_extdec_bit == 1 && second_extdec_bit == 1) {
                    set_extdec_bit(ext_result, i / 32, i, 0);
                    over_bit = 1;
                }
            } else if (first_extdec_bit == 1 && second_extdec_bit == 0 ||
                first_extdec_bit == 0 && second_extdec_bit == 1) {
                set_extdec_bit(ext_result, i / 32, i, 0);
                over_bit = 1;
            } else if (first_extdec_bit == 0 && second_extdec_bit == 0) {
                set_extdec_bit(ext_result, i / 32, i, 1);
                over_bit = 0;
            } else if (first_extdec_bit == 1 && second_extdec_bit == 1) {
                set_extdec_bit(ext_result, i / 32, i, 1);
                over_bit = 1;
            }
        }
        if (error == 1 && dec1_sign == 1) error = 2;
        setExtSign(ext_result, (dec1_sign > 0));
        setExtScale(getExtScale(ext_value_1), ext_result);
    } else if (is_equal_no_sign(ext_value_1, ext_value_2)) { // иф для а - а = 0 // перепроверит equal // на это вообще мб забить
        init_extended_decimal(ext_result); // если 10 + (-10) то что со скейлом и знаком?
    } else {
        // printf("aboba\n");
        if (is_less_no_sign(ext_value_1, ext_value_2) && getExtSign(ext_value_2)) {
            // printf("aboba1\n");
            setExtSign(&ext_value_2, 0);
            sub_no_equote(ext_value_2, ext_value_1, ext_result);
            setExtSign(ext_result, 1);
        } else if (is_less_no_sign(ext_value_1, ext_value_2) && !getExtSign(ext_value_2)) {
            // printf("aboba2\n");
            setExtSign(&ext_value_1, 0);
            sub_no_equote(ext_value_2, ext_value_1, ext_result);
            setExtSign(ext_result, 0);      
        } else if (!is_less_no_sign(ext_value_1, ext_value_2) && getExtSign(ext_value_1)) {
            // printf("aboba3\n");
            setExtSign(&ext_value_1, 0);
            sub_no_equote(ext_value_1, ext_value_2, ext_result);
            setExtSign(ext_result, 1);
        } else if (!is_less_no_sign(ext_value_1, ext_value_2) && !getExtSign(ext_value_1)) {
            // printf("aboba4\n");
            setExtSign(&ext_value_2, 0);
            sub_no_equote(ext_value_1, ext_value_2, ext_result);
            setExtSign(ext_result, 0);            
        }
    }
    // error = equate_extdec_to_dec(ext_result, ext_result); // по идее надо округлять прежде чем приравнивать
    return error;
}
