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
GCOVFLAGSLIN = -lcheck -lgcov -g -coverage -L -lrt -lpthread -lm #-lsubunit

all: clean s21_decimal test check

s21_decimal.a:
	gcc $(FLAGS) $(SOURCES) $(GCOVFLAGSLIN) -c
	ar rc s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a
	mkdir o_files
	mv *.o o_files
	
s21_dec: clean
	gcc $(FLAGS) $(SOURCES_WITH_MAIN) -g -o s21_dec
# ./s21_dec
	

test: s21_decimal.a
	gcc $(GCOVFLAGSLIN) -g -c ./tests/test.c
	gcc $(GCOVFLAGSLIN) test.o s21_decimal.a -o ./test
	./test

gcov_report: s21_decimal.a test
	gcovr .
	gcovr . --html-details coverage.html
	open coverage.html

clean:
	rm -rf *.o *.out *.gc*
	rm -rf s21_decimal s21_decimal.a s21_dec o_files coverage.* test

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	# python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	# valgrind 

rebuild:
	make clean
	make s21_decimal
	make test