#include "flags-cat.h"
void init_flags(struct flags_cat *flags) {
  (*flags).b = false;
  (*flags).v = false;
  (*flags).e = false;
  (*flags).n = false;
  (*flags).s = false;
  (*flags).t = false;
  (*flags).E = false;
  (*flags).T = false;
};
void init_long_options(struct option *long_options) {
  long_options[0].name = "number";
  long_options[0].flag = 0;
  long_options[0].has_arg = 0;
  long_options[0].val = 'n';
  (long_options)[1].name = "squeeze-blank";
  (long_options)[1].flag = 0;
  (long_options)[1].has_arg = 0;
  (long_options)[1].val = 's';
  (long_options)[2].name = "number-nonblank";
  (long_options)[2].flag = 0;
  (long_options)[2].has_arg = 0;
  (long_options)[2].val = 'b';
}

void get_flags(int argc, char *argv[], struct flags_cat *flags,
               struct option *options) {
  int rez;
  while ((rez = getopt_long(argc, argv, "benstvET", options, NULL)) != -1) {
    switch (rez) {
      case 'b':
        (*flags).b = true;
        break;
      case 'e':
        (*flags).e = true;
        break;
      case 'n':
        (*flags).n = true;
        break;
      case 's':
        (*flags).s = true;
        break;
      case 't':
        (*flags).t = true;
        break;
      case 'v':
        (*flags).v = true;
        break;
      case 'E':
        (*flags).E = true;
        break;
      case 'T':
        (*flags).T = true;
        break;
      default:
        break;
    }
  }
}

void b_option(char buffer, bool is_first, int *pInt) {
  if (is_first == true && buffer != '\n') {
    printf("%6d\t", *pInt);
    *pInt = *pInt + 1;
  }
}

void n_option(bool is_first, int *number) {
  if (is_first == true) {
    printf("%6d\t", *number);
    (*number)++;
  }
}

void t_option(char *buffer) { gnu_t_option(buffer); }

void e_option(char buffer) { gnu_e_option(buffer); }

bool s_option(char *buffer, bool *is_last_empty, bool is_first) {
  bool res = false;
  if (*buffer == '\n') {
    if (*is_last_empty && is_first) {
      res = true;
    } else if (!(*is_last_empty) && is_first) {
      *is_last_empty = true;
    } else {
      *is_last_empty = false;
      res = false;
    }
  }
  return res;
}

void v_option(char *ch, bool *print) {
  if (!isascii(*ch) && !isprint(*ch)) {
    putchar('M');
    putchar('-');
    *ch = toascii(*ch);
  }
  if (iscntrl(*ch) && *ch != '\n' && *ch != '\t') {
    putchar('^');
    putchar(*ch == 127 ? '?' : *ch + 64);
    *print = true;
  }
}

void gnu_e_option(char buffer) {
  if (buffer == '\n') {
    putchar('$');
  }
}

void gnu_t_option(char *buffer) {
  if (*buffer == '\t') {
    putchar('^');
    *buffer = 'I';
  }
}
