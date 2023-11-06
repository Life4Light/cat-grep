#include "flags-grep.h"

int main(int argc, char *argv[]){
    struct flags_grep flags;
    size_t len_line = 0;
    char filename[256];
    char *line = NULL;
    init_flags(&flags);
    get_flags(argc, argv, &flags);
    int templates_count = flags.e;
    char **templates = malloc(sizeof(char *) * templates_count);

    get_templates(argc, argv, flags, templates);
    strcpy(filename, argv[optind]);
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("n/a");
        return 1;
    }
    printf("%s", filename);
    regex_t *reg_templates = malloc(templates_count);
    int value;
    for(int i = 0; i < templates_count; i++){
        regcomp((&reg_templates)[i], templates[i], 0);
    }
    ssize_t read;
    while((read = getline(&line, &len_line, fp)) != -1){
        value = 1;
        printf("dsas");
//        for(int i = 0; i < templates_count; i++){
//            if(regexec((&reg_templates)[i], line, 0, NULL, 0) == 0){
//                value = 0;
//            }
//        }
        if(value == 0){
            printf("%s", line);
        }
    }
}