#ifndef C3_SIMPLEBASHUTILS_1_FLAGS_GREP_H
#define C3_SIMPLEBASHUTILS_1_FLAGS_GREP_H
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
typedef struct flags_grep{
    int e;
    bool i;
    bool v;
    bool c;
    bool l;
    bool n;
    int f;
    bool h;
    bool s;
}flags_grep;
void init_flags(struct flags_grep *flags);
void get_flags(int argc, char *argv[], struct flags_grep *flags);
void get_templates(int argc, char *argv[], struct flags_grep flags, char **templates);
void check_templates(char *templates, FILE *fp, struct flags_grep flags, char *filename);
char *connect_templates(char **templates, int templates_count, char **templates_files, int templates_files_count);
void grep(char *argv[],  struct flags_grep flags, int files_count, char *result_template);
void get_f_files(int argc, char *argv[], struct flags_grep flags, char **files_templates);
char *get_template_from_file(char **files, int files_count, size_t *templates_len);
#endif
