

#ifndef C3_SIMPLEBASHUTILS_1_FLAGS_CAT_H
#define C3_SIMPLEBASHUTILS_1_FLAGS_CAT_H
#include "stdbool.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

typedef struct flags_cat{
	bool b;
	bool e;
	bool n;
	bool s;
	bool t;
	bool v;
	bool E;
	bool T;
}flags_cat;


void init_flags(struct flags_cat *flags);

void init_long_options(struct option *long_options);

void e_option(const char *str);

void t_option(char *string);

void n_option(const char *buffer, int buffer_index, int *number);

void b_option(const char *buffer, int i, int *pInt);

bool s_option(char *buffer, bool *is_last_empty);

void v_option(char ch);

void get_flags(int argc, char *argv[], struct flags_cat *flags, struct option *options);

void gnu_t_option(char *string);

void gnu_e_option(const char *string);

void cat(int files_count, char *argv[], struct flags_cat flags);

void print_result(flags_cat flags, char *buffer, int *counter_n_option, int *counter_b_option);

#endif

