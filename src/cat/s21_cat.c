#include <stdio.h>
#include <malloc.h>
#include "flags-cat.h"

void print_with_echo();
int main(int argc, char *argv[]) {
	struct flags_cat flags;
	struct option long_options[3];
	init_flags(&flags);
	init_long_options(long_options);
	get_flags(argc, argv, &flags, long_options);
	int files_count = argc - optind;
	cat(files_count, argv, flags);
	return 0;
}

void cat(int files_count, char *argv[], struct flags_cat flags){
	char file_name[256];
	char* buffer = NULL;
	size_t len = 0;
	ssize_t read = 0;
	int counter_n_option = 1;
	int counter_b_option = 1;
	if (files_count == 0){
		print_with_echo();
	}
	for(int i = 0; i < files_count; i++) {
		strcpy(file_name, argv[optind + i]);
		FILE *fp = fopen(file_name, "r");
		if(!fp){
			printf("%s is not correct\n", file_name);
			continue;
		}
		if(i != 0){
			putchar('\n');
		}
		while((read = getline(&buffer, &len, fp)) != -1)
		{
			print_result(flags, buffer, &counter_n_option, &counter_b_option);
		}
		fclose(fp);
		if (buffer)
			free(buffer);
	}
}

void print_result(flags_cat flags, char *buffer, int *counter_n_option, int *counter_b_option){

	bool last_str_is_empty = false;
	bool connect_empty_lines = false;
	for(int i = 0; i < strlen(buffer); i++) {
		if(flags.s == true){
			connect_empty_lines = s_option(buffer, &last_str_is_empty);
		}
		if(flags.n == true && flags.b == false){
			n_option(buffer, i, counter_n_option);
		}
		if(flags.b == true){
			b_option(buffer, i, counter_b_option);
		}
		if(flags.e == true || flags.t == true){
			if(flags.e == true && buffer[i] == '\n'){
				e_option(&buffer[i]);
			} else if(flags.t == true && buffer[i] == '\t'){
				t_option(&buffer[i]);
			} else{
				v_option(buffer[i]);
			}
		}
		if(flags.v == true) {
			v_option(buffer[i]);
		}
		if(flags.E == true) {
			e_option(&buffer[i]);
		}
		if(flags.T == true) {
			t_option(&buffer[i]);
		}
		if(connect_empty_lines == false && (!iscntrl(buffer[i]) || buffer[i] == '\n')){
			putchar(buffer[i]);
		}
	}
}


void print_with_echo(){
	char letter;
	do{
		letter = (char)getchar();
		if(letter != EOF){
			putchar(letter);
		}
	} while(letter!=EOF);
}