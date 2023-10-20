#include <stdio.h>
#include <stdlib.h>
#include "flags-cat.h"
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
void e_option(const char *str);

void t_option(char *string);

void n_option(const char *buffer, int buffer_index, int *number);

void b_option(const char *buffer, int i, int *pInt);

bool s_option(char *buffer, bool *is_last_empty);

int main(int argc, char *argv[]){
    struct flags_cat flags;
    char filename[255];
    init_flags(&flags);
    char buffer[256];
    int rez = 0;
    int counter_n_option = 1;
    int counter_b_option = 1;
    bool is_double_empty_str = false;
    bool is_double_empty = false;
    while ((rez = getopt(argc, argv, "benst")) != -1){
        switch (rez) {
            case 'b': flags.b = true; break;
            case 'e': flags.e = true; break;
            case 'n': flags.n = true; break;
            case 's': flags.s = true; break;
            case 't': flags.t = true; break;
            default: break;
        }
    }
    for (int i = 0; i < argc; i++)
    {
        if(argv[i][0] != '-'){
            strcpy(filename, argv[i]);
        }
    }
    printf("%s\n", filename);
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("file not correct");
        return 1;
    }
    while((fgets(buffer, 256, fp)) != NULL)
    {
        size_t string_length = strlen(buffer);
        for(int i = 0; i < strlen(buffer); i++) {
            if(flags.s == true){
                 is_double_empty = s_option(buffer, &is_double_empty_str);
            }
            if(flags.n == true && flags.b == false){
                n_option(buffer, i, &counter_n_option);
            }
            if(flags.b == true){
                b_option(buffer, i, &counter_b_option);
            }
            if(flags.e == true) {
                e_option(&buffer[i]);
            }
            if(flags.t == true) { // does not work
                t_option(&buffer[i]);
            }
            if(is_double_empty == false){
                printf("%c", buffer[i]);
            }
        }
    }
    fclose(fp);
}

bool s_option(char *buffer, bool *is_last_empty) {
    if (*is_last_empty == true && strlen(buffer) == 1 && buffer[0] == '\n'){
        buffer[0] = '\0';
        return true;
    } else if(strlen(buffer) == 1 && buffer[0] == '\n'){
        *is_last_empty = true;
        return false;
    }
    *is_last_empty = false;
    return false;
}

void b_option(const char *buffer, int i, int *pInt) {
    if(i == 0 && buffer[i] != '\n' && buffer[0] != '\0'){
        printf("%d\t", *pInt);
        *pInt = *pInt + 1;
    } else if(i == 0 && buffer[0] != '\0'){
        printf("\t");
    }
}

void n_option(const char *buffer, int buffer_index, int *number) {
    if(buffer_index == 0 && buffer[0] != '\0'){
        printf("%d\t", *number);
        *number = *number + 1;
    }
}

void t_option(char *string) {
    if(string[0] == '\t'){
        printf("^");
        string[0] = 'I';
    }
}

void e_option(const char *str){
    if(str[0] == '\n'){
        printf("$");
    }
}