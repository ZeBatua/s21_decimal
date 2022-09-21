#include "../s21_decimal.h"
// весь децимал сместить на место. утерянную невмещенную часть перевести в инт -> округлить -> решить прибавлять ли единицу к основной части
int equate_extdec_to_dec(s21_extended_decimal E_decimal, s21_decimal *decimal) {
    int error = 0;
    init_decimal(decimal);
    // smart_print_exdec(E_decimal);

    s21_extended_decimal check_E_decimal;
    init_extended_decimal(&check_E_decimal);
    equate_extdec(E_decimal, &check_E_decimal);
    while (getExtScale(check_E_decimal) != 0) {
        division_by_ten(&check_E_decimal);
    }

    if (check_E_decimal.extBits[5] != 0 ||
        check_E_decimal.extBits[4] != 0 ||
        check_E_decimal.extBits[3] != 0) {
        error = 1;
    }

    if ((check_E_decimal.extBits[5] != 0 ||
         check_E_decimal.extBits[4] != 0 ||
         check_E_decimal.extBits[3] != 0) &&
        getExtSign(check_E_decimal) == 1) {
        error = 2;
    }
    if (error == 0) {
        float remainder = 0.0;
        float full_remainder = 0.0;
        
        s21_extended_decimal one;
        init_extended_decimal(&one);
        one.extBits[0] = 1;
        one.extBits[9] = E_decimal.extBits[9];

        int ten_multiply = 1;
        while (E_decimal.extBits[3] != 0 || getExtScale(E_decimal) > 28) {
            remainder = division_by_ten(&E_decimal);
            full_remainder = full_remainder + remainder * ten_multiply;
            ten_multiply *= 10;
        }

        //----округление full_emainder----//
        
        while (full_remainder >= 10) { ////////СУПЕРВАЖНОЗАТЕСТИТЬ
            full_remainder /= 10.0;
            full_remainder = round(full_remainder);
        }
        //--------------------------------//

        //-------bank_round-------//
        s21_extended_decimal bank_E_decimal;
        init_extended_decimal(&bank_E_decimal);
        equate_extdec(E_decimal, &bank_E_decimal);
        division_by_ten(&bank_E_decimal);
        multiply_extdec_by_ten(&bank_E_decimal);
        sub_no_equote(E_decimal, bank_E_decimal, &bank_E_decimal);
        if (bank_E_decimal.extBits[0] % 2 == 1 && full_remainder >= 5) {
            add_no_equote(E_decimal, one, &E_decimal);
        } else if (bank_E_decimal.extBits[0] % 2 == 1 && full_remainder < 5) {
            // nichigo
        } else if (bank_E_decimal.extBits[0] % 2 == 0 && full_remainder > 5) {
            add_no_equote(E_decimal, one, &E_decimal);
        } else if (bank_E_decimal.extBits[0] % 2 == 0 && full_remainder < 5) {
            // nichigo
        }
        //------end_bank_round-----//

        if ((E_decimal.extBits[3] != 0 ||
            E_decimal.extBits[4] != 0 ||
            E_decimal.extBits[5] != 0) &&
            getExtSign(E_decimal) == 0) {
            error = 1;
        } else if ((E_decimal.extBits[3] != 0 ||
            E_decimal.extBits[4] != 0 ||
            E_decimal.extBits[5] != 0) &&
            getExtSign(E_decimal) == 1) {
            error = 2;
        }

        decimal->bits[3] = E_decimal.extBits[9];
        decimal->bits[2] = E_decimal.extBits[2];
        decimal->bits[1] = E_decimal.extBits[1];
        decimal->bits[0] = E_decimal.extBits[0];
    }

    return error;
}
