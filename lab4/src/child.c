#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
int main(int argc, char *argv[]){
    sem_t *sem = sem_open("my_sem", 1);
    if (sem == SEM_FAILED){
	    perror("sem_open error (child)");
        exit(EXIT_FAILURE);
    }
    float res = 0;
    float x;
    while (scanf("%f",&x)!=EOF){
        res+=x;
    }

    int maxDigits = 256;
    int digits = 0;
    char res_arr[maxDigits];
    gcvt(res, maxDigits, res_arr);
    // int flag = 0;
    // for (int i = 0; i < maxDigits; i++) {
    //     if (res_arr[i]=='.') flag=1;
    //     if (res_arr[i]=='0' & flag==1){
    //         break;
    //     }
    //     digits++;
    // }
    int map_size = maxDigits;
    int fd = shm_open("shared_file", O_RDWR, 0777);
    if (ftruncate(fd, map_size) == -1){
        perror("ftruncate (child)");
	    exit(EXIT_FAILURE);
    }
    if (fd == -1){
	    perror("shm_open error (child)");
	    exit(EXIT_FAILURE);
    }
    char *mapped = (char *)mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if (mapped == MAP_FAILED){
	    perror("mmap error (child)");
        exit(EXIT_FAILURE);
    }   
    for (int i = 0; i < map_size; i++) {
        mapped[i] = res_arr[i];
    }
    if (munmap(mapped,map_size) == -1){
		perror("munmap error (child)");
		exit(EXIT_FAILURE);
	}
    sem_post(sem);
    sem_close(sem);
}