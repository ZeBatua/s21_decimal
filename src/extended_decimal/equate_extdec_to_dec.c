#include "../s21_decimal.h"
// весь децимал сместить на место. утерянную невмещенную часть перевести в инт -> округлить -> решить прибавлять ли единицу к основной части
int equate_extdec_to_dec(s21_extended_decimal E_decimal, s21_decimal *decimal) {
    int error = 0;
    init_decimal(decimal);
    
    /* 
    Так как выравнивание децимала - умножение (сдвиг влево) и прибавление скейла, 
    теперь надо сдивнуть первую значимую единицу до 8 бита.
    Таким образом мы получим целую максимум целой части и максимально вммещающийся остаток.
    */

    // smart_print_exdec(E_decimal);
    // printf("\n");
    int first_bit = get_first_non_zero_extBit(E_decimal);
    int remainder = 0;
    while (E_decimal.extBits[8] != 0) { // Надо тестить !!!!!!
        division_by_ten(&E_decimal); // не шифт а деление на 10 !!!!!!
        remainder++;
    }
    // smart_print_exdec(E_decimal);

    /* ОШИБКА
    Сдвигая децимал вправо может потеряться точность (дробная часть).
    Для этого проверяется 4 бит. Почему 4-ый:
    [9] - буффер для сдвига влево
    [8], [7], [6], [5] - биты, в которые изначально записывался decimal
    [4] - буффер для сдвига в право, для битов которые не влезают в децимал.
    010 101 101 >> 1 = 001 010 110
    Потерялась одна значимая еденица.
    Значит необходимо получить десятичную версию 4 бита и окргулить децимал.    
    */

    int mass[32] = {0}; ////!!!G@DG@87gd237gf327gf7fg327gfb NBTNNFJWEBFWUFGWIU !!!!!!!!!!!!!!!!!!!!!!!!!!
    int length_value = remainder;
    for (int i = 160; remainder > 0; remainder--, i++) {
        set_extdec_bit(&E_decimal, i / 32, i % 32, get_extdec_bit(E_decimal, i));
    }
    
    float dec_remainder = E_decimal.extBits[4];
    // printf("!!!!remainder = %d\n", dec_remainder);
    dec_remainder = dec_remainder / (10 * (length_value - 1)); // приводим число к виду 1,2345
    // printf("remainder = %d\n", dec_remainder);
    dec_remainder = round(dec_remainder);  // вот тут притэф бы чтобы убедить что окргуление работает нормально
    // printf("remainder = %d\n", dec_remainder);
    
    decimal->bits[3] = E_decimal.extBits[9];
    decimal->bits[2] = E_decimal.extBits[7];
    decimal->bits[1] = E_decimal.extBits[6];
    decimal->bits[0] = E_decimal.extBits[5];

    s21_decimal one;
    init_decimal(&one);
    one.bits[0] = 1;
    if (dec_remainder >= 5) error = s21_add(*decimal, one, decimal);
    
    return error;
}
