#include "flags-cat.h"
void init_flags(struct flags_cat *flags){
    (*flags).b = false;
	(*flags).v = false;
    (*flags).e = false;
    (*flags).n = false;
    (*flags).s = false;
    (*flags).t = false;
	(*flags).E = false;
	(*flags).T = false;

};
void init_long_options(struct option *long_options){
	long_options[0].name = "number";
	long_options[0].flag = 0;
	long_options[0].has_arg = 0;
	long_options[0].val = 'n';
	(long_options)[1].name = "squeeze-blank";
	(long_options)[1].flag = 0;
	(long_options)[1].has_arg = 0;
	(long_options)[1].val = 's';
	(long_options)[2].name = "number-nonblank";
	(long_options)[2].flag = 0;
	(long_options)[2].has_arg = 0;
	(long_options)[2].val = 'b';
}


void get_flags(int argc, char *argv[], struct flags_cat *flags, struct option *options){
	int rez;
	while ((rez = getopt_long(argc, argv, "benstvET", options, NULL)) != -1) {
		switch (rez) {
			case 'b':
				(*flags).b = true;
				break;
			case 'e':
				(*flags).e = true;
				break;
			case 'n':
				(*flags).n = true;
				break;
			case 's':
				(*flags).s = true;
				break;
			case 't':
				(*flags).t = true;
				break;
			case 'v':
				(*flags).v = true;
				break;
			case 'E':
				(*flags).E = true;
				break;
			case 'T':
				(*flags).T = true;
				break;
			default:
				break;
		}
	}
}


void b_option(const char *buffer, int i, int *pInt) {
    if(i == 0 && buffer[i] != '\n' && buffer[0] != '\0'){
		printf("%6d", *pInt);
		putchar('\t');
        *pInt = *pInt + 1;
    } else if(i == 0 && buffer[0] != '\0'){
        putchar('\t');
    }
}

void n_option(const char *buffer, int buffer_index, int *number) {
    if(buffer_index == 0 && buffer[0] != '\0'){
		putchar(' ');
		putchar(' ');
		putchar(' ');
		putchar(' ');
		putchar(*number);
		putchar('\t');
        (*number)++;
    }
}

void t_option(char *string) {
	v_option(string[0]);
	gnu_t_option(string);
}

void e_option(const char *str){
	v_option(str[0]);
	gnu_e_option(str);
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
	if(!isascii(ch) && !isprint(ch)){
		putchar('M');
		putchar('-');
		toascii(ch);
	}
    if((ch<32) && ch!= '\n' && ch != '\t'){
		putchar('^');
        putchar(ch+64);
    }
	if(ch == 127){
		putchar('?');
	}
}

void gnu_e_option(const char *str){
	if(str[0] == '\n'){
		putchar('$');
	}
}

void gnu_t_option(char *string) {
	if(string[0] == '\t'){
		putchar('^');
		string[0] = 'I';
	}
}


