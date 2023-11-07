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


void check_templates(regex_t *regex_templates, int templates_count, char **templates, FILE *fp, struct flags_grep flags, char *filename){
    int settings = 0;
    int value;
    char *line = NULL;
    int count_of_coincidences = 0;
    int number_of_line = 0;
    bool is_template_contains = false;
    size_t len_line = 0;
    if(flags.i == true){
        settings = REG_ICASE;
    }
    for(int i = 0; i < templates_count; i++){
        regcomp(&regex_templates[i], templates[i], settings);
    }
    while(getline(&line, &len_line, fp) != -1){
        number_of_line++;
        value = 1;
        if(flags.v){
            value = 0;
        }
        for(int i = 0; i < templates_count; i++){
            if(regexec(&regex_templates[i], line, 0, NULL, 0) == 0){
                value = 0;
                if(flags.v){
                    value = 1;
                }
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
}