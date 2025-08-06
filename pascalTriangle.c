#include <stdio.h>
#include <stdlib.h>

/*
=================================================================
Generate
Cria um triângulo de pascal baseado no número de linhas fornecido
=================================================================
*/
int **Generate( const int numRows, int *returnSize, int **returnColumnSizes ) {
	int **resultado = ( int ** )malloc( sizeof( int * ) * numRows );
	*returnSize = numRows;
	*returnColumnSizes = ( int * )malloc( sizeof( int ) * numRows );

	for ( int i = 0; i < numRows; i++ ) {
		( *returnColumnSizes )[i] = i + 1;
		resultado[i] = ( int * )malloc( ( i + 1 ) * sizeof( int ) );
	}

	resultado[0][0] = 1;

	for ( int i = 1; i < numRows; i++ ) {
		resultado[i][0] = 1;
		for ( int j = 1; j < i; j++ ) {
			resultado[i][j] = ( resultado[i - 1][j - 1] + resultado[i - 1][j] );
		}
		resultado[i][i] = 1;
	}

	return resultado;
}

int main( void ) {
	const int numRows = 7;
	int *returnColumnSizes = NULL;
	int returnSize = 0;

	int **pascal = Generate( numRows, &returnSize, &returnColumnSizes );

	for ( int i = 0; i < returnSize; i++ ) {
		for ( int j = 0; j < returnColumnSizes[i]; j++ ) {
			printf( "%d ", pascal[i][j] );
		}
		printf( "\n" );
	}

	for ( int i = 0; i < returnSize; i++ ) {
		free( pascal[i] );
	}
	free( pascal );
	free( returnColumnSizes );

	return 0;
}