

#ifndef C3_SIMPLEBASHUTILS_1_FLAGS_CAT_H
#define C3_SIMPLEBASHUTILS_1_FLAGS_CAT_H
#include "stdbool.h"

typedef struct flags_cat{
    bool b;
    bool e;
    bool n;
    bool s;
    bool t;
}flags_cat;
void init_flags(struct flags_cat *flags){
    (*flags).b = false;
    (*flags).e = false;
    (*flags).n = false;
    (*flags).s = false;
    (*flags).t = false;
};
#endif

