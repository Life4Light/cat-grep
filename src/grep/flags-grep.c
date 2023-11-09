#include "flags-grep.h"
void init_flags(struct flags_grep *flags){
    flags->c = false;
    flags->e = 0;
    flags->i = false;
    flags->l = false;
    flags->n = false;
    flags->v = false;
}


void get_flags(int argc, char *argv[], struct flags_grep *flags){
    int opt;
    while((opt = getopt(argc, argv, "ce:linv")) != -1){
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
            default:
                break;

        }
    }
}

void get_templates(int argc, char *argv[], struct flags_grep flags, char **templates){
    int opt;
    if(flags.e == 0){
        templates[0] = argv[optind];
        optind++;
    }
    else {
        optind = 1;
        flags.e = 0;
        while((opt = getopt(argc, argv, "e:")) != -1){
            switch (opt) {
                case 'e':
                    flags.e++;
                    templates[flags.e-1] = optarg;
                    break;
                default:
                    break;
            }
        }
    }

}


void check_templates(char *templates, FILE *fp, struct flags_grep flags, char *filename){
    int settings = 0;
    int value;
    char *line = NULL;
    int count_of_coincidences = 0;
    int number_of_line = 0;
    bool is_template_contains = false;
    size_t len_line = 0;
    regex_t regex_templates;
    if(flags.i == true){
        settings = REG_ICASE;
    }
    regcomp(&regex_templates, templates, REG_EXTENDED);

    while(getline(&line, &len_line, fp) != -1){
        number_of_line++;
        value = 1;
        if(flags.v){
            value = 0;
        }
        if(regexec(&regex_templates, line, 0, NULL, 0) == 0){
            value = 0;
            if(flags.v){
                value = 1;
            }
        }
        if(value == 0){
            is_template_contains = true;
            if(flags.n){
                printf("%d:", number_of_line);
            }
            if(!flags.c && !flags.l) {
                printf("%s", line);
            } else{
                count_of_coincidences++;
            }
        }
    }
    if(flags.l && is_template_contains){
        printf("%s", filename);
    }
    if(flags.c){
        printf("%d", count_of_coincidences);
    }
    regfree(&regex_templates);
}


char *connect_templates(char **templates, int templates_count){
    size_t templates_length = 0;
    char *result_template;
    for(int i = 0; i < templates_count; i++){
        templates_length += strlen(templates[i]);
    }
    result_template = calloc((templates_length + templates_count), sizeof(char));
    strcat(result_template, templates[0]);
    for(int i = 1; i < templates_count; i++){
        strcat(result_template, "|");
        strcat(result_template, templates[i]);
    }
    return result_template;
}

void grep(char *argv[],  struct flags_grep flags, int files_count, char *result_template){
    char filename[256];
    for(int i = 0; i < files_count; i++){
        strcpy(filename, argv[optind + i]);
        FILE *fp = fopen(filename, "r");
        if(fp){
            check_templates(result_template, fp, flags, filename);
            if(i != files_count-1){
                printf("\n");
            }
        } else{
            printf("%s: No such file or directory", filename);
        }
    }
}