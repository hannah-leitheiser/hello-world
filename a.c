#include <stdio.h>

const char* t() { return NULL; }

main() {

    char * a = t();
    if(a) { printf("a"); }
    else
    {printf("B"); }
}
