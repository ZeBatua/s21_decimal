CFLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc
GFLAGS = -coverage
LDFLAGS = -lgcov
TFLAGS = -lcheck
OBJECTS = *.o
ASAN = -fsanitize=address

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
	$(CC) $(SOURCES) $(ASAN) -c
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a

test: s21_decimal.a
	$(CC) $(ASAN) s21_test.c s21_decimal.a -o test $(TFLAGS)
	./test

gcov_report: clean
	$(CC) $(SOURCES) $(ASAN) $(CFLAGS) $(LDFLAGS) $(GFLAGS) -c
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a
	$(CC) $(ASAN) $(LDFLAGS) s21_test.c s21_decimal.a -o test $(TFLAGS)
	./test
	gcovr .
	gcovr --html-details -o report.html
	open ./report.html

check:
	# cppcheck --enable=all --suppress=missingIncludeSystem .
	CK_FORK=no leaks --atExit -- ./test

clean: 
	rm -rf *.o *.out *.gc
	rm -rf s21_decimal s21_decimal.a s21_dec o_files coverage.* test *dSYM *.css *.html *.gcda *.gcno gcov_report *.info report
