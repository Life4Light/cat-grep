CC = /usr/bin/gcc
FLAGS = -Wall -Werror -Wextra
TARGET = main_executable_module.c
all: s21_grep

s21_grep: s21_grep.c flags-grep.c
	$(CC) $(FLAGS) s21_grep.c flags-grep.c -o s21_grep

rebuild:
	clean s21_grep

clean:
	rm s21_grep -rf *.a *.o
