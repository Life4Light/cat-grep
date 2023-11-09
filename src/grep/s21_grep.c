#include "flags-grep.h"

int main(int argc, char *argv[]){
    struct flags_grep flags;
    init_flags(&flags);
    get_flags(argc, argv, &flags);
    int templates_count = flags.e;
    int templates_file_count = flags.f;
    if(flags.e == 0){
        templates_count = 1;
    }
    char **templates = calloc( templates_count, sizeof(char *));
    char **templates_files = calloc(templates_file_count, sizeof(char *));
    get_f_files(argc, argv, flags, templates_files);
    get_templates(argc, argv, flags, templates);
    int files_count = argc-optind;
    if(files_count == 0){
        printf("n/a");
        return 1;
    }
    char *result_template = connect_templates(templates, templates_count, templates_files, templates_file_count);
    grep(argv, flags, files_count, result_template);
    free(templates);
    free(templates_files);
}