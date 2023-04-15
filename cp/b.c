#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

    int pcb = atoi(argv[1]);
    int pab = atoi(argv[2]);  
    
    size_t size,size1;

    while (read(pab, &size, sizeof(size_t)) > 0) { 
        read(pcb, &size1, sizeof(size_t));
        printf("b - from a: %zu\n", size);
        printf("b - from c: %zu\n", size1);
    }

    close(pcb);
    close(pab);
    
    return 0;
}