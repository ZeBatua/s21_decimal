#FLAGS = -Wall -Werror -Wextra -std=c11
SOURCES = \
	./secondary_functions/Bit_operations/*.c \
	./secondary_functions/convert_dec/*.c \
	./secondary_functions/dec_to_back_string/*.c \
	./secondary_functions/float_functions/*.c \
	./secondary_functions/Get:Set_Sign:Scale/*.c \
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
	main.c \
	./secondary_functions/Bit_operations/*.c \
	./secondary_functions/convert_dec/*.c \
	./secondary_functions/dec_to_back_string/*.c \
	./secondary_functions/float_functions/*.c \
	./secondary_functions/Get:Set_Sign:Scale/*.c \
	./secondary_functions/NoSE/*.c \
	./secondary_functions/Print/*.c \
	./secondary_functions/shifts/*.c \
	./secondary_functions/tmp/*.c \
	./main_functions/Another_functions/*.c \
	./main_functions/Arithmetic_Operators/*.c \
	./main_functions/Comparison_Operators/*.c \
	./extended_decimal/*.c \
	./main_functions/Convertors_and_parsers/*.c


OBJECTS = *.o
GCOVFLAGSLIN = -lcheck -lgcov -L -lrt -lpthread -lm #-lsubunit -coverage

all: clean s21_decimal.a test check

s21_decimal.a:
	@gcc $(FLAGS) $(SOURCES) $(GCOVFLAGSLIN) -c
	@ar rc s21_decimal.a $(OBJECTS)
	@ranlib s21_decimal.a
	@mkdir o_files
	@mv *.o o_files
	
s21_dec: clean
	@gcc $(FLAGS) $(SOURCES_WITH_MAIN) -g -lcheck -o s21_dec
	./s21_dec
	

test: clean s21_decimal.a
	@gcc $(GCOVFLAGSLIN) -g -c tests/test.c
	@gcc $(GCOVFLAGSLIN) test.o s21_decimal.a -o ./test
	./test

test2: clean s21_decimal.a
	@gcc $(GCOVFLAGSLIN) s21_test.c s21_decimal.a -o ./test2
	./test2


gcov_report: s21_decimal.a test
	gcovr .
	gcovr . --html-details coverage.html
	open coverage.html

clean:
	@rm -rf *.o *.out *.gc*
	@rm -rf s21_decimal s21_decimal.a s21_dec o_files coverage.* test test2 *.dSYM

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	# python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	# valgrind 

rebuild:
	make clean
	make s21_decimal
	make test