#include <stdio.h>
#include "flags-cat.h"


int main(int argc, char *argv[]) {
	struct flags_cat flags;
	struct option long_options[3];
	int err;
	init_flags(&flags);
	init_long_options(long_options);
	get_flags(argc, argv, &flags, long_options);
	int files_count = argc - optind;
	err = cat(files_count, argv, flags);
	if (err == 1){
		printf("incorrect file");
		return 1;
	}
	return 0;
}

int cat(int files_count, char *argv[], struct flags_cat flags){
	char file_name[256];
	char buffer[256];
	for(int i = 0; i < files_count; i++) {
		strcpy(file_name, argv[1]);
		FILE *fp = fopen(file_name, "r");
		if(!fp){
			return 1;
		}
		while((fgets(buffer, 256, fp)) != NULL)
		{
			print_result(flags, buffer);
		}
		printf("\n");
		fclose(fp);
	}
	return 0;
}

void print_result(flags_cat flags, char *buffer){
	int counter_n_option = 1;
	int counter_b_option = 1;
	bool last_str_is_empty = false;
	bool connect_empty_lines = false;
	for(int i = 0; i < strlen(buffer); i++) {
		if(flags.s == true){
			connect_empty_lines = s_option(buffer, &last_str_is_empty);
		}
		if(flags.n == true && flags.b == false){
			n_option(buffer, i, &counter_n_option);
		}
		if(flags.b == true){
			b_option(buffer, i, &counter_b_option);
		}
		if(flags.e == true) {
			v_option(buffer[i]);
			e_option(&buffer[i]);
		}
		if(flags.t == true) {
			v_option(buffer[i]);
			t_option(&buffer[i]);
		}
		if(flags.E == true) {
			e_option(&buffer[i]);
		}
		if(flags.T == true) {
			t_option(&buffer[i]);
		}
		if(connect_empty_lines == false && (!iscntrl(buffer[i]) || buffer[i] == '\n')){
			printf("%c", buffer[i]);
		}
	}
}
