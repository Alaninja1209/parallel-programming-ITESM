#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <threads.h>
#define N 300

void multiplicaMatriz(int matriz[N][N], int matrizDos[N][N], int producto[N][N]){
    int i,j,k;

    #pragma omp parallel for private(i,j,k) shared (matriz,matrizDos,producto)
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            producto[i][j] = 0;
            for(k = 0; k < N; k++){
                producto[i][j] = producto[i][j] + (matriz[i][k] * matrizDos[k][j]);
            }
        }
    }
}

void generaMatriz(int matriz[N][N]){
    int i, j;

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            matriz[i][j] = 1 + rand() % 5;
        }
    }
}

void imprimeMatriz(int matriz[N][N]){
    int i, j;
    for(i = 0; i < N; i++){
        for(j  = 0; j < N; j++){
            printf(" %d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]){
    srand(time(NULL));

    int ThreadsNumber = strtol(argv[1], NULL, 10);
    omp_set_num_threads(ThreadsNumber);

    int matriz[N][N];
    int matrizDos[N][N];
    int producto[N][N];

    generaMatriz(matriz);
    generaMatriz(matrizDos);

    /*imprimeMatriz(matriz);
    printf("\n");
    imprimeMatriz(matrizDos);
    printf("\n");*/
    multiplicaMatriz(matriz, matrizDos, producto);

    //printf("\n");
    imprimeMatriz(producto);
    return 0;
}
