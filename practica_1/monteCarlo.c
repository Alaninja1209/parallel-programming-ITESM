#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 

#define points 10000
pthread_mutex_t lock;

long int pointsInsideCircle = 0;

void* monteCarloPi(void * numThreads){
    int counter = 0;
    double x, y;
    srand(time(NULL));

    for(int i = 0; i < (points / (int)numThreads); i++){
        x = (double)(rand() % (points)) / points;
        y = (double)(rand() % (points)) / points;
        if(((x * x) + (y * y)) <= 1){
            counter++; 
        }
    }

    pthread_mutex_lock(&lock);
    pointsInsideCircle += counter;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    //Obtain number of threads
    int numThreads = atoi(argv[1]);
    pthread_t threads[numThreads];
    int rc;

    //Time
    clock_t start, end;

    double pi, time;
    
    start = clock();
    for(int i = 0; i < numThreads; i++){
        rc = pthread_create(&threads[i], NULL, monteCarloPi, (void*)(numThreads)); 
    }

    for(int j = 0; j < numThreads; j++){
        pthread_join(threads[j], NULL);
    }

    //Kill the mutex
    pthread_mutex_destroy(&lock);

    pi = 4.0 * (double) pointsInsideCircle/points; 

    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Estimation of pi with %d threads. Time: %f seconds. Pi: %f\n ", numThreads, time, pi);

    return 0;
}