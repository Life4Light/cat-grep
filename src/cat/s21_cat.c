#include <stdio.h>
#include <stdlib.h>
#include "flags-cat.h"



int main(int argc, char *argv[]) {
	struct flags_cat flags;
	char file_name[256];
	init_flags(&flags);
	char buffer[256];
	int rez;
	int files_count;
	bool is_double_empty_str = false;
	bool is_double_empty = false;
	while ((rez = getopt(argc, argv, "benst")) != -1) {
		switch (rez) {
			case 'b':
				flags.b = true;
				break;
			case 'e':
				flags.e = true;
				break;
			case 'n':
				flags.n = true;
				break;
			case 's':
				flags.s = true;
				break;
			case 't':
				flags.t = true;
				break;
			default:
				break;
		}
	}
	files_count = argc - optind;
	for (int file_counter = 0; file_counter < files_count; file_counter++){
		int counter_n_option = 1;
		int counter_b_option = 1;
		strcpy(file_name, argv[optind + file_counter]);
		FILE *fp = fopen(file_name, "r");
		if(!fp){
			printf("file not correct");
			return 1;
		}
		while((fgets(buffer, 256, fp)) != NULL)
		{
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
					v_option(buffer[i]);
					e_option(&buffer[i]);
				}
				if(flags.t == true) {
					v_option(buffer[i]);
					t_option(&buffer[i]);
				}
				if(is_double_empty == false && (!iscntrl(buffer[i]) || buffer[i] == '\n')){
					printf("%c", buffer[i]);
				}
			}
		}
		fclose(fp);
	}
}



