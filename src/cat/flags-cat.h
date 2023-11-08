

#ifndef C3_SIMPLEBASHUTILS_1_FLAGS_CAT_H
#define C3_SIMPLEBASHUTILS_1_FLAGS_CAT_H
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "stdbool.h"

typedef struct flags_cat {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
  bool E;
  bool T;
} flags_cat;

void init_flags(struct flags_cat *flags);

void init_long_options(struct option *long_options);

void e_option(char buffer);

void t_option(char *buffer);

void n_option(bool is_first, int *number);

void b_option(char buffer, bool is_first, int *pInt);

bool s_option(char *buffer, bool *is_last_empty, bool is_first);

void v_option(char *ch, bool *print);

void get_flags(int argc, char *argv[], struct flags_cat *flags,
               struct option *options);

void gnu_t_option(char *buffer);

void gnu_e_option(char buffer);

void cat(int files_count, char *argv[], struct flags_cat flags);

void print_result(flags_cat flags, char buffer, int *counter_n_option,
                  int *counter_b_option, bool *is_first,
                  bool *last_str_is_empty);

#endif
