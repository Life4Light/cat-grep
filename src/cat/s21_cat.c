#include "stdio.h"
#include "stdlib.h"
#include "flags-cat.h"
#include "stdbool.h"
#include <unistd.h>

int main(int argc, char *argv[]){
    struct flags_cat flags;
    init_flags(flags);
    int rez = 0;
    while ( (rez = getopt(argc, argv, "benst")) != -1){
        switch (rez) {
            case 'b': flags.b = true; printf("dsasd"); break;
            case 'e': flags.e = true; break;
            case 'n': flags.n = true; break;
            case 's': flags.s = true; printf("sdasd"); break;
            case 't': flags.t = true; break;
        } // switch
    } // while

}