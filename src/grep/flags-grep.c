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
    while((opt = getopt(argc, argv, "ce:ilnv")) != -1){
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
