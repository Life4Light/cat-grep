#include "flags-grep.h"
void init_flags(struct flags_grep *flags){
    flags->c = false;
    flags->e = 0;
    flags->i = false;
    flags->l = false;
    flags->n = false;
    flags->v = false;
	flags->f = 0;
}


void get_flags(int argc, char *argv[], struct flags_grep *flags){
    int opt;
    while((opt = getopt(argc, argv, "ce:linvf:")) != -1){
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
                flags->f +=1;
            default:
                break;

        }
    }
}
void get_f_files(int argc, char *argv[], struct flags_grep flags, char **files_templates){
    int opt;
	if(flags.f> 0 ){
		flags.f = 0;
		optind = 1;
		while((opt = getopt(argc, argv, "ce:linvf:")) != -1){
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
void get_templates(int argc, char *argv[], struct flags_grep flags, char **templates){
    int opt;
    if(flags.e == 0 && flags.f == 0){
        templates[0] = argv[optind];
		optind++;
    }
    else {
        optind = 1;
        flags.e = 0;
        while((opt = getopt(argc, argv, "ce:linvf:")) != -1){
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


void check_templates(char *templates, FILE *fp, struct flags_grep flags, char *filename){
    int settings = REG_EXTENDED;
    int value;
    char *line = NULL;
	size_t     nmatch = 2;
	regmatch_t pmatch[2];
    int count_of_coincidences = 0;
    int number_of_line = 0;
    bool is_template_contains = false;
    size_t len_line = 0;
    regex_t regex_templates;
    if(flags.i == true){
        settings |= REG_ICASE;
    }
    regcomp(&regex_templates, templates, settings);

    while(getline(&line, &len_line, fp) != -1){
        number_of_line++;
        value = 1;
        if(flags.v){
            value = 0;
        }
        if(regexec(&regex_templates, line, nmatch, pmatch, 0) == 0){
			while(regexec(&regex_templates, line, nmatch, pmatch, 0) == 0){
				printf("%.*s",
					   	pmatch[0].rm_eo - pmatch[0].rm_so, &line[pmatch[0].rm_so]);
						line = &line[pmatch[0].rm_eo];
						printf("\naaaaaa\n");
			}
			value = 0;
            if(flags.v){
                value = 1;
            }
        }
        if(value == 0){
            is_template_contains = true;
			if(!flags.c && !flags.l) {
				if(flags.n ){
					printf("%d:", number_of_line);
				}
				printf("%s", line);
			} else{
				count_of_coincidences++;
			}

        }
    }
    if(flags.l && is_template_contains){
        printf("%s", filename);
    } else if(flags.c){
        printf("%d", count_of_coincidences);
    }
    regfree(&regex_templates);
}


char *connect_templates(char **templates, int templates_count, char **templates_files, int templates_files_count){
	size_t templates_from_file_len = 0;
	char *templates_from_file = NULL;
	char *result_template;
	size_t templates_len = 0;
	if(templates_files_count > 0){
		templates_from_file = get_template_from_file(templates_files, templates_files_count, &templates_from_file_len);
	}
	for(int i = 0; i < templates_count; i++){
		templates_len += strlen(templates[i]);
    }
	result_template = calloc((templates_len + templates_count + templates_from_file_len), sizeof(char));
	for(int i = 0; i < templates_count; i++){
		if(i == 0){
			strcpy(result_template, templates[i]);
		}else{
			strcat(result_template, "|");
			strcat(result_template, templates[i]);
		}
	}
	if(templates_count == 0){
		strcpy(result_template,templates_from_file);
	} else if(templates_from_file_len > 0){
		strcat(result_template, "|");
		strcat(result_template,templates_from_file);
	}
	return result_template;
}

char *get_template_from_file(char **files, int files_count, size_t *templates_len) {
	char *line = NULL;
	char *templates;
	int templates_count = 0;
	size_t len_line;
	ssize_t chars_read;
	size_t len_templates = 0;
	for (int i = 0; i < files_count; i++) {
		FILE *fp = fopen(files[i], "r");
		if (!fp) {
			printf("%s: No such file or directory\n", files[i]);
		} else {
			while ((chars_read = getline(&line, &len_line, fp)) != -1) {
				templates_count++;
				len_templates += chars_read;
				if(chars_read > 0 && line[chars_read-1] == '\n') {
					len_templates--;
				}
			}
		}
	}
	*templates_len = len_templates + templates_count;
	templates = calloc(*templates_len, sizeof(char *));
	templates_count = 0;
	for (int i = 0; i < files_count; i++) {
		FILE *fp = fopen(files[i], "r");
		if(fp){
			while ((chars_read = getline(&line, &len_line, fp)) != -1) {
				if(chars_read > 0 && line[chars_read-1] == '\n') {
					line[chars_read-1] = '\0';
					// special care for windows line endings:
					if(chars_read > 1 && line[chars_read-2] == '\r') line[chars_read-2] = '\0';
				}
				if(templates_count == 0){
					strcpy(templates, line);
				} else{
					strcat(templates, "|");
					strcat(templates, line);
				}
				templates_count++;
			}
			fclose(fp);
		}
	}

	return templates;
}

void grep(char *argv[],  struct flags_grep flags, int files_count, char *result_template) {
    char filename[256];
    for(int current_file = 0; current_file < files_count; current_file++) {
		if(strlen(argv[optind + current_file]) > 255){
			printf("The file must be no more than 256 characters");
		}else{
			strcpy(filename, argv[optind + current_file]);
			FILE *fp = fopen(filename, "r");
			if(fp) {
				check_templates(result_template, fp, flags, filename);
				if(current_file != files_count - 1){
					printf("\n");
				}
			} else {
				printf("%s: No such file or directory\n", filename);
			}
		}

    }
}


