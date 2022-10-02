CFLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc
CCOV = -fprofile-arcs -ftest-coverage
#GFLAGS = -coverage -g
LDFLAGS = -lgcov
TFLAGS = -lcheck -lm -pthread -L -lrt 
UFLAG = -lsubunit
OBJECTS = *.o
#ASAN = -g -fsanitize=adress
var = $(shell pkg-config --cflags --libs check)

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

# SOURCES_WITH_MAIN = \
# 	main.c \
# 	./secondary_functions/Bit_operations/*.c \
# 	./secondary_functions/convert_dec/*.c \
# 	./secondary_functions/dec_to_back_string/*.c \
# 	./secondary_functions/float_functions/*.c \
# 	./secondary_functions/GetSet_SignScale/*.c \
# 	./secondary_functions/NoSE/*.c \
# 	./secondary_functions/Print/*.c \
# 	./secondary_functions/shifts/*.c \
# 	./secondary_functions/tmp/*.c \
# 	./main_functions/Another_functions/*.c \
# 	./main_functions/Arithmetic_Operators/*.c \
# 	./main_functions/Comparison_Operators/*.c \
# 	./extended_decimal/*.c \
# 	./main_functions/Convertors_and_parsers/*.c
var = $(shell pkg-config --cflags --libs check)


all: clean s21_decimal.a 

s21_decimal.a:
	$(CC) $(SOURCES) $(ASAN) $(CFLAGS) $(TFLAGS) $(LDFLAGS) $(GFLAGS)-c
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a
#	mkdir o_files
#	mv *.o o_files

s21_test.o:
	$(CC) $(ASAN) $(var) -c s21_test.c

test: s21_decimal.a s21_test.o
	$(CC) $(ASAN) $(LDFLAGS) $(var) s21_test.o s21_decimal.a -o test $(TFLAGS)
	./test

gcov_report: s21_decimal.a test	
	lcov -t 'gcov_report' -o gcov_report.info -c -d .
	genhtml -o gcov_report gcov_report.info
    

# s21_dec: clean
# 	$(CC) $(CFLAGS) $(SOURCES_WITH_MAIN) $(TFLAGS) -g -o s21_dec
# 	./s21_dec

check:
#    cppcheck --enable=all --suppress=missingIncludeSystem .
	leaks -atExit -exclude -- ./test

clean: 
	rm -rf *.o *.out *.gc
	rm -rf s21_decimal s21_decimal.a s21_dec o_files coverage.* test *dSYM *.css *.html *.gcda *.gcno

rebuild:
	make clean
	make s21_decimal	
	make test

	
