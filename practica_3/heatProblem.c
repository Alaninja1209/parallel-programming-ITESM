#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <threads.h>
#include <omp.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t lock;

int  heatRoom[10][6][7];
char heatMap[6][7] = {{'C', 'C', 'C', 'C', 'C', 'C', 'C'},{'C', 'C', 'C', 'C', 'C', 'C', 'C'},{'C', 'C', 'H', 'H', 'H', 'C', 'C'},{'C', 'C', 'H', 'H', 'H', 'C', 'C'},{'C', 'C', 'H', 'H', 'H', 'C', 'C'},{'C', 'C', 'C', 'C', 'C', 'C', 'C'}};

void delay(int seconds){
    int ms = 1000 * seconds;
    clock_t start_time = clock();
    while(clock() < start_time + ms);
}

void heatEquation(){
    int i,j,k;

    #pragma omp parallel for private(i,j,k) shared (heatRoom)
    for(i = 0; i < 10; i++){
        for(j = 0; j < 6; j++){
            for(k = 0; j < 7; j++){
                heatRoom[i + 1][j][k] = 0.02 *(heatRoom[i][j + 1][k] + heatRoom[i][j - 1][k] + heatRoom[i][j][k + 1] + heatRoom[i][j][k - 1] - 4*heatRoom[i][j][k]) + heatRoom[i][j][k];
            }
        }
    }
}

void fillRoom(){ //Complete de room with -1 values
    int i,j,k;
    for(i = 0; i < 10; i++){
        for(j = 0; j < 6; j++){
            for(k = 0; k < 7; k++){
                heatRoom[i][j][k] = - 1;
            }
        }
    }
}

void* defineRoomTemp(void * numThreads){ //Complete room with his respective temperatures
    int i,j,k;

    for(i = 0; i < 10; i++){
        for(j = 0; j < 6; j++){
            for(k = 0; k < 7; k++){
                if(heatMap[j][k] == 'C'){
                    heatRoom[i][j][k] = rand()% 59;
                }
                if(heatMap[j][k] == 'H'){
                    heatRoom[i][j][k] = rand()% 40 + 60;
                }
            }
        }
    }

}

void printRoom(){
    int i,j,k;
    for(i = 0; i < 10; i++){
        for(j = 0; j < 6; j++){
            for(k = 0; k < 7; k++){
                printf(" %d " , heatRoom[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    clock_t start, end;
    double time;

    start = clock();
    int rc;

    int threadsNumber = strtol(argv[1], NULL, 10);
    pthread_t threads[threadsNumber];
    omp_set_num_threads(threadsNumber);

    fillRoom();

    for(int i = 0; i < threadsNumber; i++){
        rc = pthread_create(&threads[i], NULL, defineRoomTemp, (void*)(threadsNumber));
    }

    for(int j = 0; j < threadsNumber; j++){
        pthread_join(threads[j], NULL);
    }

    heatEquation();
    delay(200);
    printRoom();
    end = clock();

    time = (double)(end - start)/CLOCKS_PER_SEC;

    printf("Total duration %f", time);
    printf("\n");

    return 0;
}
