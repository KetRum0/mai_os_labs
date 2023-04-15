#include <lab3.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

main(int argc, char * argv[]){
    int n;
    int threadCount;
    scanf("%d",&n);
    scanf("%d",&threadCount);
    if ((threadCount <= 0) | (n <= 0))
    {
        perror("Wrong arguments");
		exit(EXIT_FAILURE);
    }
    double result = chance(n, threadCount);
    printf("%g\n",result);
}