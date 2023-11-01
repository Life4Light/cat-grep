CC = /usr/bin/gcc
FLAGS = -Wall -Werror -Wextra
TARGET = main_executable_module.c
FILE_PATH_1 = ../build/cat
all: s21_cat

s21_cat: flags-cat.c flags-cat.h s21_cat.c
	$(CC) $(FLAGS) s21_cat.c flags-cat.c flags-cat.h -o s21_cat

rebuild:
	clean s21_cat

clean:
	rm -rf $FILE_PATH_1 *.a *.o

run:
	./$(FILE_PATH_1)