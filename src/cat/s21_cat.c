#include <stdio.h>

#include "flags-cat.h"

void print_with_echo();
int main(int argc, char *argv[]) {
  struct flags_cat flags;
  struct option long_options[3];
  init_flags(&flags);
  init_long_options(long_options);
  get_flags(argc, argv, &flags, long_options);
  int files_count = argc - optind;
  cat(files_count, argv, flags);
  return 0;
}

void cat(int files_count, char *argv[], struct flags_cat flags) {
  char file_name[256];
  char buffer;
  int counter_n_option = 1;
  int counter_b_option = 1;

  bool is_first = true;
  if (files_count == 0) {
    print_with_echo();
  }
  for (int i = 0; i < files_count; i++) {
      bool last_str_is_empty = false;
      bool connect_empty_lines = false;
      strcpy(file_name, argv[optind + i]);
    FILE *fp = fopen(file_name, "r");
    if (!fp) {
      printf("%s is not correct\n", file_name);
      continue;
    }
    if (i != 0) {
      putchar('\n');
    }
    do {
      buffer = getc(fp);
      if (buffer == EOF) {
        break;
      }
      print_result(flags, buffer, &counter_n_option, &counter_b_option,
                   &is_first, &last_str_is_empty, &connect_empty_lines);
    } while (buffer != EOF);
    fclose(fp);
  }
}

void print_result(flags_cat flags, char buffer, int *counter_n_option,
                  int *counter_b_option, bool *is_first, bool *last_str_is_empty, bool *connect_empty_lines) {
    bool print = false;
  if (flags.s == true) {
    print = s_option(&buffer, last_str_is_empty, *is_first);
  }
  if(print == false){
      if (flags.n == true && flags.b == false) {
          n_option(buffer, *is_first, counter_n_option);
      }
      if (flags.b == true) {
          b_option(buffer, *is_first, counter_b_option);
      }
      if (flags.e == true || flags.t == true) {
          if (flags.e == true && buffer == '\n') {
              e_option(buffer);
          } else if (flags.t == true && buffer == '\t') {
              t_option(&buffer);
          } else if(flags.e == true || flags.t == true){
              if(buffer != '\n' && buffer != '\t'){
                  v_option(buffer, &print);
              }
          }
      }
      if (flags.v == true && (flags.e == false || flags.t == false) && !print) {
          v_option(buffer, &print);
      }
      if (flags.E == true) {
          e_option(buffer);
      }
      if (flags.T == true) {
          t_option(&buffer);
      }
  }
  if (!print){
    putchar(buffer);
  }
  if (buffer == '\n') {
    *is_first = true;
  } else {
    *is_first = false;
  }
}

void print_with_echo() {
  char letter;
  do {
    letter = (char)getchar();
    if (letter != EOF) {
      putchar(letter);
    }
  } while (letter != EOF);
}