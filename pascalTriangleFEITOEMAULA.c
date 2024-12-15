#include<stdio.h>
#include<stdlib.h>

int** Generate(int numRows, int* returnSize, int** returnColumnSizes){
    *returnSize = numRows;
    int **resultado = (int**) malloc(sizeof(int*) * numRows );
    *returnColumnSizes = (int*) malloc(sizeof(int) * numRows );
    
    for ( int i=0; i<numRows; i++ ) {
        (*returnColumnSizes)[i] = i + 1;
        resultado[i] = (int*) malloc((i+1) * sizeof(int));
    }
    
    resultado[0][0] = 1;
    
    for ( int i=1; i<numRows; i++ ) {
        resultado[i][0] = 1;
        for ( int j=1; j<i; j++ ) {
            resultado[i][j] = resultado[i-1][j-1] + resultado[i-1][j];
        }
        resultado[i][i] = 1;
    }
    return resultado;
}

int main() {
    int numRows = 5;
    int *returnColumnSizes = NULL;
    int returnSize = 0;

    int **pascal = Generate(numRows, &returnSize, &returnColumnSizes);
    
    for ( int i = 0; i < returnSize; i++ ) {
        for ( int j = 0; j < returnColumnSizes[i]; j++ ) {
            printf("%d ", pascal[i][j]);
        }
        printf("\n");
    }
    
    for ( int i = 0; i < returnSize; i++ ) {
        free(pascal[i]);
    }
    free(pascal);
    free(returnColumnSizes);

    return 0;
}