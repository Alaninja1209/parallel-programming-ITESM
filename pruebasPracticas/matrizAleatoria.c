#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define N 4

//Ejecucion de la multiplacion de matrices
void multiplicaMatriz(int matriz[N][N], int matrizDos[N][N], int producto[N][N]){
    int i,j,k;

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            producto[i][j] = 0;
            for(k = 0; k < N; k++){
                producto[i][j] = producto[i][j] + (matriz[i][k] * matrizDos[k][j]);
            }
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

//Generar la matriz con numero aleatorias de rango 1-5 de tamaño N*N
void generaMatriz(int matriz[N][N]){
    int i, j;

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            matriz[i][j] = 1+rand() % 5;
        }
    }
}

int main(){
    srand(time(NULL));

    int matriz[N][N];
    int matrizDos[N][N];
    int producto[N][N];

    generaMatriz(matriz);
    generaMatriz(matrizDos);

    imprimeMatriz(matriz);
    printf("\n");
    imprimeMatriz(matrizDos);
    printf("\n");
    multiplicaMatriz(matriz, matrizDos, producto);

    printf("\n");
    imprimeMatriz(producto);
    return 0;
}
