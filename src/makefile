#FLAGS = -Wall -Werror -Wextra -std=c11
SOURCES = ./secondary_functions/*.c \
	./main_functions/Another_functions/*.c \
	./main_functions/Arithmetic_Operators/*.c \
	./main_functions/Comparison_Operators/*.c \
	./main_functions/Convertors_and_parsers/*.c
SOURCES_WITH_MAIN = main.c ./secondary_functions/*.c \
	./main_functions/Another_functions/*.c \
	./main_functions/Arithmetic_Operators/*.c \
	./main_functions/Comparison_Operators/*.c \
	./main_functions/Convertors_and_parsers/*.c
OBJECTS = *.o
GCOVFLAGSLIN = -lcheck -lgcov -coverage -L -lrt -lpthread -lm #-lsubunit

all: clean s21_decimal test check

s21_decimal.a:
	gcc $(FLAGS) $(SOURCES) -c
	ar rc s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a
	mkdir o_files
	mv *.o o_files

s21_dec:
	gcc $(FLAGS) $(SOURCES_WITH_MAIN) -o s21_dec
	./s21_dec
	

test: clean s21_decimal
	gcc $(GCOVFLAGSLIN) -g -c ./tests/test.c
	gcc $(GCOVFLAGSLIN) test.o s21_decimal.a -o ./test
	./test


clean:
	rm -rf *.o *.out *.gc*
	rm -rf s21_decimal s21_decimal.a s21_dec o_files

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	# python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	# valgrind 

rebuild:
	make clean
	make s21_decimal
	make test