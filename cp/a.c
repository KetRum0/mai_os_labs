#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>


char* ReadString(FILE* stream) {
    if(feof(stream)) {
        return NULL;
    }

    const int chunkSize = 256;
    char* buffer = (char*)malloc(chunkSize);
    int bufferSize = chunkSize;

    if(!buffer) {
        printf("Couldn't allocate buffer");
        exit(EXIT_FAILURE);
    }

    int readChar;
    int idx = 0;
    while((readChar = getc(stream)) != EOF) {
        buffer[idx++] = readChar;

        if(idx == bufferSize) {
            buffer = realloc(buffer, bufferSize + chunkSize);
            bufferSize += chunkSize;
        }

        if(readChar == '\n') {
            break;
        }
    }

    buffer[idx] = '\0';

    return buffer;
}

size_t str_length(char *str) {
    size_t length = 0;
    for (int i = 0; str[i] != '\n'; i++) {
        length++;
    }
    return length;
}

int main() {
    int ab[2];
    int ac[2];
    int ca[2];
    int cb[2];

    if (pipe(ab) == -1){
		perror("pipe error");
		exit(EXIT_FAILURE);
	}

    if (pipe(ac) == -1){
		perror("pipe error");
		exit(EXIT_FAILURE);
	}

    if (pipe(ca) == -1){
		perror("pipe error");
		exit(EXIT_FAILURE);
	}

    if (pipe(cb) == -1){
		perror("pipe error");
		exit(EXIT_FAILURE);
	}

    int id1 = fork();

    if (id1 < 0) {
        perror("fork error");
		exit(EXIT_FAILURE);
    }
    else if (id1 == 0) { 
        close(ac[1]);
        close(ca[0]);
        close(cb[0]);
        close(ab[0]);
        close(ab[1]);

        char pac[3];
        sprintf(pac, "%d", ac[0]); 

        char pca[3];
        sprintf(pca, "%d", ca[1]); 

        char pcb[3];
        sprintf(pcb, "%d", cb[1]); 
        
        if (execl("./c", "./c", pac, pca, pcb, NULL) == -1){
			perror("execl error");
			exit(EXIT_FAILURE);
		}

    }
    else { 
        int id2 = fork();
        if (id2 < 0) {
            perror("fork error");
		    exit(EXIT_FAILURE);
        }
        else if (id2 == 0) {
            close(ac[0]);
            close(ac[1]);
            close(ca[0]);
            close(ca[1]);
            close(cb[1]);
            close(ab[1]);

            char pcb[3];
            sprintf(pcb, "%d", cb[0]);

            char pab[3];
            sprintf(pab, "%d", ab[0]);
           
            if ( execl("./b", "./b",  pcb, pab, NULL) == -1){
			    perror("execl error");
			    exit(EXIT_FAILURE);
		    }
            
        }
        else { 
            close(ac[0]);
            close(ca[1]);
            close(ab[0]);
            close(cb[1]);
            close(cb[0]);
         
            char *str = NULL; 
            while ((str = ReadString(stdin)) != NULL) { 
                size_t size = str_length(str);
                write(ac[1], &size, sizeof(size_t)); 
                write(ac[1], str, size); 
                write(ab[1], &size, sizeof(size_t));
                int ok; 
                read(ca[0], &ok, sizeof(ok)); 
            }
            close(ca[0]);
            close(ac[1]);
            close(ab[1]);
         }
    }

    return 0;
}