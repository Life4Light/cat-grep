#include "flags-grep.h"

void init_flags(struct flags_grep *flags) {
  flags->c = false;
  flags->e = 0;
  flags->i = false;
  flags->l = false;
  flags->n = false;
  flags->v = false;
  flags->f = 0;
  flags->h = false;
  flags->s = false;
  flags->o = false;
}

void get_flags(int argc, char *argv[], struct flags_grep *flags) {
  int opt;
  while ((opt = getopt(argc, argv, "ce:linvf:hso")) != -1) {
    switch (opt) {
      case 'c':
        flags->c = true;
        break;
      case 'e':
        flags->e += 1;
        break;
      case 'i':
        flags->i = true;
        break;
      case 'l':
        flags->l = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 'v':
        flags->v = true;
        break;
      case 'f':
        flags->f += 1;
        break;
      case 'h':
        flags->h = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 'o':
        flags->o = true;
        break;
      default:
        break;
    }
  }
}
void get_f_files(int argc, char *argv[], struct flags_grep flags,
                 char **files_templates) {
  int opt;
  if (flags.f > 0) {
    flags.f = 0;
    optind = 1;
    while ((opt = getopt(argc, argv, "ce:linvf:hso")) != -1) {
      switch (opt) {
        case 'f':
          files_templates[flags.f] = optarg;
          flags.f++;
          break;
        default:
          break;
      }
    }
  }
}
void get_templates(int argc, char *argv[], struct flags_grep flags,
                   char **templates) {
  int opt;
  if (flags.e == 0 && flags.f == 0) {
    templates[0] = argv[optind];
    optind++;
  } else {
    optind = 1;
    flags.e = 0;
    while ((opt = getopt(argc, argv, "ce:linvf:hso")) != -1) {
      switch (opt) {
        case 'e':
          templates[flags.e] = optarg;
          flags.e++;
          break;
        default:
          break;
      }
    }
  }
}

void check_templates(char *templates, FILE *fp, struct flags_grep flags,
                     char *filename) {
  int settings = REG_EXTENDED;
  int count_of_coincidences = 0;
  bool is_template_contains = false;
  regex_t regex_templates;
  if (flags.i == true) {
    settings |= REG_ICASE;
  }
  regcomp(&regex_templates, templates, settings);
  check_string_from_pattern(flags, fp, regex_templates, filename,
                            &is_template_contains, &count_of_coincidences);
  c_l_flags(flags, is_template_contains, filename, count_of_coincidences);
  regfree(&regex_templates);
}

char *connect_templates(char **templates, int templates_count,
                        char **templates_files, int templates_files_count) {
  size_t templates_from_file_len = 0;
  char *templates_from_file = NULL;
  char *result_template = NULL;
  size_t templates_len = 0;
  if (templates_files_count > 0) {
    templates_from_file = get_template_from_file(
        templates_files, templates_files_count, &templates_from_file_len);
  }
  for (int i = 0; i < templates_count; i++) {
    templates_len += strlen(templates[i]);
  }
  if (templates_len + templates_count + templates_from_file_len > 0) {
    result_template =
        calloc((templates_len + templates_count + templates_from_file_len),
               sizeof(char));
  }
  if (result_template) {
    for (int i = 0; i < templates_count; i++) {
      if (i == 0) {
        strcpy(result_template, templates[i]);
      } else {
        strcat(result_template, "|");
        strcat(result_template, templates[i]);
      }
    }
    if (templates_count == 0) {
      strcpy(result_template, templates_from_file);
    } else if (templates_from_file_len > 0) {
      strcat(result_template, "|");
      strcat(result_template, templates_from_file);
    }
  }
  free(templates_from_file);

  return result_template;
}

char *get_template_from_file(char **files, int files_count,
                             size_t *templates_len) {
  char *line = NULL;
  char *templates;
  int templates_count = 0;
  size_t len_line;
  ssize_t chars_read;
  size_t len_templates = 0;
  for (int i = 0; i < files_count; i++) {
    FILE *fp = fopen(files[i], "r");
    if (!fp) {
      fprintf((stderr), "%s: No such file or directory\n", files[i]);
    } else {
      while ((chars_read = getline(&line, &len_line, fp)) != -1) {
        templates_count++;
        len_templates += chars_read;
        if (chars_read > 0 && line[chars_read - 1] == '\n') {
          len_templates--;
        }
      }
      fclose(fp);
      if (line) {
        free(line);
        line = NULL;
      }
    }
  }
  *templates_len = len_templates + templates_count;
  templates = calloc(*templates_len, sizeof(char *));
  templates_count = 0;
  for (int i = 0; i < files_count; i++) {
    FILE *fp = fopen(files[i], "r");
    if (fp) {
      connect_templates_from_file(fp, templates_count, templates);
      fclose(fp);
    }
  }

  return templates;
}

void grep(char *argv[], struct flags_grep flags, int files_count,
          char *result_template) {
  char filename[256];
  if (files_count < 2) {
    flags.h = true;
  }
  for (int current_file = 0; current_file < files_count; current_file++) {
    if (strlen(argv[optind + current_file]) > 255) {
      fprintf((stderr), "The file must be no more than 256 characters");
    } else {
      strcpy(filename, argv[optind + current_file]);
      FILE *fp = fopen(filename, "r");
      if (fp) {
        check_templates(result_template, fp, flags, filename);
        fclose(fp);
      } else if (flags.s == false) {
        fprintf((stderr), "grep: %s: No such file or directory\n", filename);
      }
    }
  }
}

void o_option(struct flags_grep flags, regex_t *regex_templates, char *filename,
              int number_of_line, char *line, bool *is_contains_template) {
  size_t nmatch = 2;
  regmatch_t pmatch[2];
  while (regexec(regex_templates, line, nmatch, pmatch, 0) == 0) {
    *is_contains_template = true;
    if (!flags.l && !flags.c) {
      if (!flags.h) {
        printf("%s:", filename);
      }
      if (flags.n) {
        printf("%d:", number_of_line);
      }
      printf("%.*s\n", pmatch[0].rm_eo - pmatch[0].rm_so,
             &line[pmatch[0].rm_so]);
    }

    line = &line[pmatch[0].rm_eo];
  }
  if (flags.v) {
    *is_contains_template = !(*is_contains_template);
  }
}

void c_l_flags(flags_grep flags, bool is_template_contains, char *filename,
               int count_of_coincidences) {
  if (flags.l && is_template_contains) {
    printf("%s\n", filename);
  } else if (flags.c) {
    if (!(flags.c && flags.l && count_of_coincidences == 0)) {
      if (!flags.h) {
        printf("%s:", filename);
      }
      printf("%d\n", count_of_coincidences);
    }
  }
}

void print_res(flags_grep flags, int value, bool *is_template_contains,
               char *filename, int number_of_line, char *line,
               int *count_of_coincidences) {
  if (value == 0) {
    *is_template_contains = true;
    if (!flags.c && !flags.l) {
      if (!flags.h) {
        printf("%s:", filename);
      }
      if (flags.n) {
        printf("%d:", number_of_line);
      }
      if (line[strlen(line) - 1] == '\n') {
        printf("%s", line);
      } else {
        printf("%s\n", line);
      }

    } else {
      (*count_of_coincidences)++;
    }
  };
}

void change_eof(ssize_t chars_read, char *line) {
  if (chars_read > 0 && line[chars_read - 1] == '\n') {
    line[chars_read - 1] = '\0';
    // special care for windows line endings:
    if (chars_read > 1 && line[chars_read - 2] == '\r')
      line[chars_read - 2] = '\0';
  }
}

void connect_templates_from_file(FILE *fp, int templates_count,
                                 char *templates) {
  char *line = NULL;
  ssize_t chars_read = 0;
  size_t len_line;
  while ((chars_read = getline(&line, &len_line, fp)) != -1) {
    change_eof(chars_read, line);
    if (templates_count == 0) {
      strcpy(templates, line);
    } else {
      strcat(templates, "|");
      strcat(templates, line);
    }
    templates_count++;
  }
  if (line) {
    free(line);
  }
}

void check_string_from_pattern(struct flags_grep flags, FILE *fp,
                               regex_t regex_templates, char *filename,
                               bool *is_template_contains,
                               int *count_of_coincidences) {
  char *line = NULL;
  size_t len_line = 0;
  size_t nmatch = 2;
  regmatch_t pmatch[2];
  int number_of_line = 0;
  int value = 0;
  while (getline(&line, &len_line, fp) != -1) {
    number_of_line++;
    value = 1;
    if (flags.v) {
      value = 0;
    }
    if (regexec(&regex_templates, line, nmatch, pmatch, 0) == 0) {
      if ((flags.o && !flags.v) || (flags.o && (flags.l || flags.c))) {
        v_option(flags, count_of_coincidences);
        o_option(flags, &regex_templates, filename, number_of_line, line,
                 is_template_contains);
      }
      value = 0;
      if (flags.v) {
        value = 1;
      }
    } else if (flags.o && flags.v && (flags.l || flags.c)) {
      (*count_of_coincidences)++;
      *is_template_contains = true;
    }
    if (!flags.o) {
      print_res(flags, value, is_template_contains, filename, number_of_line,
                line, count_of_coincidences);
    }
  }
  if (line) {
    free(line);
  }
}

void v_option(struct flags_grep flags, int *count_of_coincidences) {
  if (!flags.v) {
    (*count_of_coincidences)++;
  }
}