CC = /usr/bin/gcc
FLAGS = -Wall -Werror -Wextra
TARGET = main_executable_module.c
FILE_PATH_1 = ../build/cat
all: s21_cat

flags-cat.o: flags-cat.c
	$CC -c $FLAGS flags-cat.c
s21_cat: flags-cat.c flags-cat.o
	$CC $FLAGS s_21_cat.c flags-cat.o -o $FILE_PATH_1

rebuild:
	clean s21_cat

clean:
	rm -rf $FILE_PATH_1 *.a *.o

run:
	./$(FILE_PATH_1)