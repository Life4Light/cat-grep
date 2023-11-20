CC = /usr/bin/gcc
FLAGS = -std=c11 -Wall -Werror -Wextra
all: s21_cat

s21_cat: s21_cat.c flags-cat.c
	$(CC) $(FLAGS) s21_cat.c flags-cat.c -o s21_cat

rebuild: clean s21_cat

clean:
	rm s21_cat -rf *.a *.o

run:
	./s21_cat