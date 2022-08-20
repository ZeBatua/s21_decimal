#FLAGS = -Wall -Werror -Wextra -std=c11
SOURCES = ./secondary_functions/*.c \
	./main_functions/Another_functions/*.c \
	./main_functions/Arithmetic_Operators/*.c \
	./main_functions/Comparison_Operators/*.c \
	./main_functions/Convertors_and_parsers/*.c
OBJECTS = *.o
GCOVFLAGSLIN = -lcheck -lgcov -coverage # -lsubunit -lrt -lpthread -lm

all: s21_decimal test check

s21_decimal:
	gcc $(FLAGS) $(SOURCES) -c
	ar rc s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a


test: s21_decimal
	gcc $(GCOVFLAGSLIN) -g -c ./tests/test.c
	gcc $(GCOVFLAGSLIN) test.o s21_decimal.a -o ./test
	./test
clean:
	rm -rf *.o *.out
	rm -rf s21_decimal 

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	# python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	# valgrind ./s21_cat

rebuild:
	make clean
	make s21_decimal
	make test