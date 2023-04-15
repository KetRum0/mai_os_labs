#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int pac = atoi(argv[1]);
    int pca = atoi(argv[2]); 
    int pcb = atoi(argv[3]);
    
    size_t size,size1;
    while (read(pac, &size, sizeof(size_t)) > 0) {
        char *str = (char*) malloc(size); 
        if (str == NULL) {
            perror("malloc error");
		    exit(EXIT_FAILURE);
        }
        read(pac, str, size); 
        printf("c - from a: %s\n", str);
        size1 = strlen(str);
        write(pcb, &size1, sizeof(size_t)); 
        int ok = 1;
        write(pca, &ok, sizeof(int));
        free(str);
    }

    close(pac);
    close(pca);
    close(pcb);

    return 0;
}