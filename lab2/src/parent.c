#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int ParentRoutine(char *filename){

	// char name[256];
	// scanf("%s",name);
	int file;
	if ((file = open(filename, O_RDONLY))==-1){
		perror("open error");
		exit(EXIT_FAILURE);
	}

	int fd[2];
	if (pipe(fd) == -1){
		perror("pipe error");
		exit(EXIT_FAILURE);
	}

	int id = fork();
	if (id == -1){
		perror("fork error");
		exit(EXIT_FAILURE);
        
	} else if (id == 0){ //child
        close(fd[0]);
        dup2(file,STDIN_FILENO);
        close(file);
        dup2(fd[1],STDOUT_FILENO);
        close(fd[1]);
		if (execlp("./child", "./child", NULL) == -1){
			perror("execlp error");
			exit(EXIT_FAILURE);
		}
	
    } else { //parent
		close(fd[1]);
        close(file);
		float result;
		if (read(fd[0], &result, sizeof(float)) == -1){
			perror("read from pipe error");
			exit(EXIT_FAILURE);
		}
        close(fd[0]);
        // printf("%g\n",result);
		return result;	
	}
}