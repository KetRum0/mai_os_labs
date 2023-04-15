#define INT_MAX 2147483647
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
int* count;
int deck[] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12};

typedef struct arguments{
    int rounds_for_thread;
    int num_of_thread;
    int seed_thread;
}Arguments;

void * thread_func(void* args){
    int card1, card2;
    Arguments * Args = (Arguments *) args;
    int r = Args -> rounds_for_thread;
    int n = Args -> num_of_thread;
    int seed = Args -> seed_thread;
    
    for (int i = 0; i < r; i++){    
        card1 = 0;
        card2 = 0;
        while (card1==card2){
        card1 = rand_r(&seed) % 52;
        card2 = rand_r(&seed) % 52;
        }
        if (deck[card1] == deck[card2]){
            count[n]++;
        }
        
    }
}
double chance(int n, int threadCount){
    int rounds, threads;
    rounds = n;
    threads = threadCount;
    int rounds_thread = rounds/threads;
    count = (int *) calloc(threads, sizeof(int));
    pthread_t *th = (pthread_t *) calloc(threads, sizeof(pthread_t));
    Arguments a[threads];
    for (int i = 0; i < threads; i++){
        a[i].num_of_thread = i;
        a[i].rounds_for_thread = rounds_thread;
        a[i].seed_thread = rand();
    }
    for (int i = 0; i < threads; i++){
        if (pthread_create(&th[i], NULL, &thread_func, (void*) &a[i]) != 0){
            perror("pthread_create error");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < threads; i++){
        if (pthread_join(th[i],NULL) != 0){
            perror("thread_join error");
            exit(EXIT_FAILURE);
        }
    }
    int sum_count = 0;
    for (int i = 0; i < threads; i++){
        sum_count += count[i];
    }
    // end = time(NULL);
    // int time_taken = end - start;
    // printf("Time taken to execute in seconds : %d\n", time_taken);
    // printf("%g\n",(double) sum_count/rounds);
    // printf("Real chance:          %g\n", (double) 3/51);
    double result = (double) sum_count/rounds;
    return result;
}