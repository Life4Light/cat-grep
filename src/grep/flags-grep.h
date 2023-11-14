#ifndef C3_SIMPLEBASHUTILS_1_FLAGS_GREP_H
#define C3_SIMPLEBASHUTILS_1_FLAGS_GREP_H

#define _GNU_SOURCE

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
typedef struct flags_grep {
  int e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  int f;
  bool h;
  bool s;
  bool o;
} flags_grep;

void init_flags(struct flags_grep *flags);
void get_flags(int argc, char *argv[], struct flags_grep *flags);
void get_templates(int argc, char *argv[], struct flags_grep flags,
                   char **templates);
void check_templates(char *templates, FILE *fp, struct flags_grep flags,
                     char *filename);
char *connect_templates(char **templates, int templates_count,
                        char **templates_files, int templates_files_count);
void grep(char *argv[], struct flags_grep flags, int files_count,
          char *result_template);
void get_f_files(int argc, char *argv[], struct flags_grep flags,
                 char **files_templates);
char *get_template_from_file(char **files, int files_count,
                             size_t *templates_len);
void o_option(struct flags_grep flags, regex_t regex_templates, char *filename,
              int number_of_line);
void c_l_flags(flags_grep flags, bool is_template_contains, char *filename,
               int count_of_coincidences);
void n_option(flags_grep flags, int value, bool *is_template_contains,
              char *filename, int number_of_line, char *line,
              int *count_of_coincidences);
#endif
