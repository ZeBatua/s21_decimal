#include "../s21_decimal.h"
// весь децимал сместить на место. утерянную невмещенную часть перевести в инт -> округлить -> решить прибавлять ли единицу к основной части
int equate_extdec_to_dec(s21_extended_decimal E_decimal, s21_decimal *decimal) {
    int error = 0;
    init_decimal(decimal);


    /*
        Избавимся на запасной версии поступившего децимала от дробной части.
        Это потребуется для проверка что decimal <= pow(2, 97) - 1
        (pow(2, 97) - 1) - эта запись гдесь decimal во всех 96 битах равен 1
     
    */

    s21_extended_decimal check_E_decimal;
    init_extended_decimal(&check_E_decimal);
    equate_extdec(E_decimal, &check_E_decimal);
    while (getExtScale(check_E_decimal) != 0) {
        division_by_ten(&check_E_decimal);
    }

        
    /* 
        проверка что децимал не остался переполненым
        операцией выше была удалена дробная часть
        если после этого целая не умещается в биты 5 4 3
        то он переполнен
    */

    if (check_E_decimal.extBits[6] != 0 ||
        check_E_decimal.extBits[7] != 0 ||
        check_E_decimal.extBits[8] != 0) {
        error = 1;
    }

    /* 
        аналогично для отрицательного переполнения
    */

    if ((check_E_decimal.extBits[6] != 0 ||
        check_E_decimal.extBits[7] != 0 ||
        check_E_decimal.extBits[8] != 0) &&
        getExtSign(check_E_decimal) == 1) {
        error = 2;
    }


    /* 
    Так как выравнивание децимала - умножение (сдвиг влево) и прибавление скейла, 
    теперь надо сдивнуть первую значимую единицу до 8 бита.
    Таким образом мы получим максимум целой части и максимально вмещающийся остаток.
    */

    // smart_print_exdec(E_decimal);
    // printf("\n");
    int remainder = 0;
    printf("tutachke4\n");
    smart_print_exdec(E_decimal);
    
    s21_extended_decimal one;
    init_extended_decimal(&one);
    one.extBits[3] = 1;
    one.extBits[9] = E_decimal.extBits[9];

    int first_bit = get_first_non_zero_extBit(E_decimal);
    while (E_decimal.extBits[6] != 0) {
        smart_print_exdec(E_decimal);
        remainder = division_by_ten(&E_decimal);
        printf("||||| remainder = %d |||\n", remainder);
        if (remainder >= 5) {
            printf("||| remainder = %d |||\n", remainder);
            add_no_equote(E_decimal, one, &E_decimal);
        }
    }

    if ((E_decimal.extBits[6] != 0 ||
        E_decimal.extBits[7] != 0 ||
        E_decimal.extBits[8] != 0) &&
        getExtSign(E_decimal) == 0) {
        error = 1;
    } else if ((E_decimal.extBits[6] != 0 ||
        E_decimal.extBits[7] != 0 ||
        E_decimal.extBits[8] != 0) &&
        getExtSign(E_decimal) == 1) {
        error = 2;
    }




    decimal->bits[3] = E_decimal.extBits[9];
    decimal->bits[2] = E_decimal.extBits[5];
    decimal->bits[1] = E_decimal.extBits[4];
    decimal->bits[0] = E_decimal.extBits[3];


    
    printf("tutachke10\n");

    // if (remainder >= 5) error = s21_add(*decimal, one, decimal);

    printf("tutachke11\n");

    return error;
}
