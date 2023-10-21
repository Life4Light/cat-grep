

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

typedef struct flags_cat{
	bool b;
	bool e;
	bool n;
	bool s;
	bool t;
}flags_cat;
void init_flags(struct flags_cat *flags);

void e_option(const char *str);

void t_option(char *string);

void n_option(const char *buffer, int buffer_index, int *number);

void b_option(const char *buffer, int i, int *pInt);

bool s_option(char *buffer, bool *is_last_empty);

void v_option(const char ch);




#endif

