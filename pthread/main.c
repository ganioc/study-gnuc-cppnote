#include <stdio.h>

#include "llst.h"
#include "multi.h"


int main(){
    printf("pthread main() =>\n");

    testllst();

    testPthread();

    return 0;
}