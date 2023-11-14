CC = /usr/bin/gcc
FLAGS = -std=c11 -Wall -Werror -Wextra
all: s21_grep

s21_grep: s21_grep.c flags-grep.c
	$(CC) $(FLAGS)  s21_grep.c flags-grep.c -o s21_grep

rebuild:
	clean s21_grep

clean:
	rm s21_grep -rf *.a *.o
