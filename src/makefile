#CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic -fanalyzer
CC = gcc
CCOV = -fprofile-arcs -ftest-coverage 
GFLAGS = --coverage
LDFLAGS = -lgcov
TFLAGS = -lcheck 
UFLAG = -lsubunit -lm -pthread -L -lrt -lsubunit -pthread
OBJECTS = *.o
#ASAN = -g -fsanitize=adress
var = $(shell pkg-config --cflags --libs check)

SOURCES = \
	./secondary_functions/Bit_operations/*.c \
	./secondary_functions/convert_dec/*.c \
	./secondary_functions/dec_to_back_string/*.c \
	./secondary_functions/float_functions/*.c \
	./secondary_functions/GetSet_SignScale/*.c \
	./secondary_functions/NoSE/*.c \
	./secondary_functions/Print/*.c \
	./secondary_functions/shifts/*.c \
	./secondary_functions/tmp/*.c \
	./main_functions/Another_functions/*.c \
	./main_functions/Arithmetic_Operators/*.c \
	./main_functions/Comparison_Operators/*.c \
	./extended_decimal/*.c \
	./main_functions/Convertors_and_parsers/*.c
SOURCES_WITH_MAIN = \
	my_main.c \
	./secondary_functions/Bit_operations/*.c \
	./secondary_functions/convert_dec/*.c \
	./secondary_functions/dec_to_back_string/*.c \
	./secondary_functions/float_functions/*.c \
	./secondary_functions/GetSet_SignScale/*.c \
	./secondary_functions/NoSE/*.c \
	./secondary_functions/Print/*.c \
	./secondary_functions/shifts/*.c \
	./secondary_functions/tmp/*.c \
	./main_functions/Another_functions/*.c \
	./main_functions/Arithmetic_Operators/*.c \
	./main_functions/Comparison_Operators/*.c \
	./extended_decimal/*.c \
	./main_functions/Convertors_and_parsers/*.c


all: clean s21_decimal.a test gcov_report 

s21_decimal.a:
	@$(CC) $(SOURCES) $(var) $(ASAN) $(CFLAGS) $(TFLAGS) $(LDFLAGS) -c 
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a

test: s21_decimal.a
	$(CC) $(ASAN) s21_decimal.a s21_test.c  $(TFLAGS) -o test 
	./test

gcov_report: clean
	@$(CC) $(CCOV) --coverage $(var)  s21_test.c $(SOURCES) -lcheck -lm -lpthread -o s21_test.out 
	./s21_test.out 
	lcov -t "s21_test.out" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index-sort-f.html
	rm -rf coverage.* *dSYM *.css *.html *.gcda *.gcno

s21_dec: clean s21_decimal.a
	@$(CC) $(CFLAGS) s21_decimal.a main.c $(TFLAGS) -g -o s21_dec
	./s21_dec

check: test
	cppcheck s21_decimal.h $(SOURCES)
	# cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	# python3 ../materials/linters/cpplint.py --extensions=c s21_decimal.h $(SOURCES)
	CK_FORK=no leaks --atExit -- ./test
	rm -rf ./CPPLINT*


clean: 
	rm -rf *.o *.out *.gc
	rm -rf s21_decimal s21_decimal.a s21_dec o_files coverage.* test *dSYM *.css *.html *.gcda *.gcno *.gcov gcov_report *.info report


rebuild:
	make clean
	make s21_decimal	
	make test

valgrind: clean s21_decimal.a
	$(CC) $(ASAN) $(LDFLAGS) $(TFLAGS) s21_test.c s21_decimal.a -o test 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose  --log-file=valgrind-out.txt ./test
