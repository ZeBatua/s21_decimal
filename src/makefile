#FLAGS = -Wall -Werror -Wextra -std=c11

all: s21_decimal test check

s21_decimal:
	gcc $(FLAGS) main.c ./secondary_functions/getBit.c \
	./secondary_functions/setScale.c ./secondary_functions/getScale.c \
	./main_functions/Another_functions/s21_truncate.c ./secondary_functions/init_decimal.c \
	./secondary_functions/equate_decimal.c ./secondary_functions/division_by_ten.c \
	./secondary_functions/shift_right.c ./secondary_functions/alt_add.c \
	./secondary_functions/shift_left.c ./secondary_functions/alt_sub.c \
	./secondary_functions/get_decimal_bit.c ./secondary_functions/getSign.c \
	./secondary_functions/setBit.c ./secondary_functions/set_decimal_bit.c -o s21_decimal

test:
	

clean:
	rm -rf *.o *.out *cat.txt
	rm -rf s21_decimal 

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	# python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	# valgrind ./s21_cat

rebuild:
	make clean
	make all