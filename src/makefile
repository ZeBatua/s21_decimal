FLAGS = -Wall -Werror -Wextra -std=c11

all: s21_decimal

s21_cat: 
	gcc $(FLAGS) s21_cat.c -o s21_cat

test:
	chmod +rwx test.sh
	./test.sh

clean:
	rm -rf *.o *.out *cat.txt
	rm -rf s21_cat

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	valgrind ./s21_cat

rebuild:
	make clean
	make all