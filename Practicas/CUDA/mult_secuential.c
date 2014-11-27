#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main( int argc, char* argv[] ){

  int m, n, p, q, c, d, k, sum = 0, i;
  const int N = atoi(argv[1]);

  int **A;
  A = ( int** ) malloc( N * sizeof( int* ) );
  int **B;
  B = ( int** ) malloc( N * sizeof( int* ) );
  int **C;
  C = ( int** ) malloc( N * sizeof( int* ) );

  for( i = 0; i < N; i++ ){
    A[i] = (int*) malloc( N * sizeof(int) );
    B[i] = (int*) malloc( N * sizeof(int) );
    C[i] = (int*) malloc( N * sizeof(int) );
  }

  // Initialize matrices
  for( c = 0; c < N; c++ ){
    for( d = 0; d < N; d++ ){
      if( c != d ){
	A[c][d] = 0;
	B[c][d] = 0;
      } else{
	A[c][d] = 1;
	B[c][d] = 1;
      }
      C[c][d] = 0;
    }
  }

  double start = omp_get_wtime( );
  for ( c = 0 ; c < N ; c++ ){
    for ( d = 0 ; d < N ; d++ ){
      for ( k = 0 ; k < N ; k++ ){
	sum = sum + A[c][k] * B[k][d];
      }
      C[c][d] = sum;
      sum = 0;
    }
  }
  double end = omp_get_wtime( );
  printf("\t Time = %.2f ms\n", ( end - start ) * 1000 );

  return 0;
}
