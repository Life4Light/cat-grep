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
struct flags_grep{
    int e;
    bool i;
    bool v;
    bool c;
    bool l;
    bool n;
};
void init_flags(struct flags_grep *flags);
void get_flags(int argc, char *argv[], struct flags_grep *flags);
void get_templates(int argc, char *argv[], struct flags_grep flags, char **templates);

#endif
