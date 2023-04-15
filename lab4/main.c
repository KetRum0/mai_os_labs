
#include "parent.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char name[256];
	scanf("%s",name);
    float result;
    result = ParentRoutine(name);
    printf("%g\n",result);
    return 0;
}