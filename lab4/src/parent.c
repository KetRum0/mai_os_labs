#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

float ParentRoutine(char *filename){
	// char name[256];
	// scanf("%s",name);
	int file;
	if ((file = open(filename, O_RDONLY))==-1){
		perror("open error");
		exit(EXIT_FAILURE);
	}
	sem_t *sem = sem_open("my_sem", O_CREAT,S_IRUSR | S_IWUSR, 0);
    if (sem == SEM_FAILED){
		perror("sem_open error");
        exit(EXIT_FAILURE);
    }
	int id = fork();
	if (id == -1){
		perror("fork error");
		exit(EXIT_FAILURE);
        
	} else if (id == 0){ //child
        dup2(file,STDIN_FILENO);
		close(file);
		if (execlp("./child", "./child", NULL) == -1){
			perror("execlp error");
			exit(EXIT_FAILURE);
		}
	
    } else { //parent
		int fd = shm_open("shared_file", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
		if (fd == -1){
			perror("shm_open error (parent)");
			exit(EXIT_FAILURE);
		}
        sem_wait(sem);
		sem_close(sem);
        struct stat s;
        fstat(fd, &s);
        int map_size = s.st_size;
        char *mapped = (char *) mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (mapped == MAP_FAILED) {
            perror("mmap error (parent)");
        	exit(EXIT_FAILURE);
        }
		close(fd);
		float result = atof(mapped);
		if (munmap(mapped,map_size) == -1){
			perror("munmap error (parent)");
			exit(EXIT_FAILURE);
		}
		if (shm_unlink("shared_file") == -1){
			perror("shm_unlink error");
			exit(EXIT_FAILURE);
        }
		
		return result;
	}
	
}
