CC = /usr/bin/gcc
FLAGS = -std=c11 -Wall -Werror -Wextra
TARGET = main_executable_module.c
all: s21_cat

s21_cat: s21_cat.c flags-cat.c flags-cat.h
	$(CC) $(FLAGS) s21_cat.c flags-cat.c -o s21_cat

rebuild: clean s21_cat

clean:
	rm s21_cat -rf *.a *.o

run:
	./s21_cat