#include "flags-grep.h"

int main(int argc, char *argv[]){
    struct flags_grep flags;
    char filename[256];
    init_flags(&flags);
    get_flags(argc, argv, &flags);
    int templates_count = flags.e;
    if(flags.e == 0){
        templates_count = 1;
    }
    regex_t *regex_templates = malloc(sizeof(regex_t) * templates_count);
    char **templates = malloc(sizeof(char *) * templates_count);
    get_templates(argc, argv, flags, templates);
    int files_count = argc-optind;
    if(files_count == 0){
        printf("n/a");
        return 1;
    }
    for(int i = 0; i < files_count; i++){
        strcpy(filename, argv[optind + i]);
        FILE *fp = fopen(filename, "r");
        if(!fp){
            printf("n/a");
            return 1;
        }
        check_templates(regex_templates, templates_count, templates, fp, flags, filename);
        if(i != files_count-1){
            printf("\n");
        }
    }
    for(int i = 0; i < templates_count; i++){
       regfree(&regex_templates[i]);
    }
    free(regex_templates);

}