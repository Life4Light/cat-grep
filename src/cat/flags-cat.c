#include "flags-cat.h"
void init_flags(struct flags_cat *flags){
    (*flags).b = false;
    (*flags).e = false;
    (*flags).n = false;
    (*flags).s = false;
    (*flags).t = false;
};
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

bool s_option(char *buffer, bool *is_last_empty) {
    bool res = false;
    if (*is_last_empty == true && strlen(buffer) == 1 && buffer[0] == '\n'){
        buffer[0] = '\0';
        res = true;
    } else if(strlen(buffer) == 1 && buffer[0] == '\n'){
        *is_last_empty = true;
        res = false;
    } else{
        *is_last_empty = false;
    }
    return res;
}

void v_option(const char ch){
    if((ch<32 || ch ==127) && ch!= '\n' && ch != '\t'){
        printf("^%c", ch+64);
    }
}

