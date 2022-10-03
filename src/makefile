# CFLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc
CCOV = -fprofile-arcs -ftest-coverage
GFLAGS = -coverage -g
LDFLAGS = -lgcov
TFLAGS = -lcheck
OBJECTS = *.o
#ASAN = -g -fsanitize=adress

SOURCES = \
	./secondary_functions/Bit_operations/*.c \
	./secondary_functions/convert_dec/*.c \
	./secondary_functions/float_functions/*.c \
	./secondary_functions/GetSet_SignScale/*.c \
	./secondary_functions/NoSE/*.c \
	./secondary_functions/shifts/*.c \
	./main_functions/Another_functions/*.c \
	./main_functions/Arithmetic_Operators/*.c \
	./main_functions/Comparison_Operators/*.c \
	./extended_decimal/*.c \
	./main_functions/Convertors_and_parsers/*.c 

all: clean s21_decimal.a 

s21_decimal.a: clean
	$(CC) $(SOURCES) $(ASAN) $(CFLAGS) $(LDFLAGS) $(GFLAGS) -c
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a

test: s21_decimal.a
	$(CC) $(ASAN) $(LDFLAGS) s21_test.c s21_decimal.a -o test $(TFLAGS)
	./test

gcov_report: s21_decimal.a
	$(CC) $(CCOV) --coverage s21_test.c $(SOURCES) -lcheck -o s21_test.out 
	./s21_test.out 
	lcov -t "s21_test.out" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index-sort-f.html
	rm -rf coverage.* *dSYM *.css *.html *.gcda *.gcno

check:
#    cppcheck --enable=all --suppress=missingIncludeSystem .
	leaks -atExit -exclude -- ./test

clean: 
	rm -rf *.o *.out *.gc
	rm -rf s21_decimal s21_decimal.a s21_dec o_files coverage.* test *dSYM *.css *.html *.gcda *.gcno gcov_report *.info report
