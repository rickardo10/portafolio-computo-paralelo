#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[]){
  int rnk, sz, n, I, info, i, chunk;
  double *x, *y, *buff;
  n = atoi(argv[1]);
  x = (double*)malloc(n*sizeof(double));
  y = (double*)malloc(n*sizeof(double));
  buff = (double*)malloc(n*sizeof(double));
  MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &info);
  MPI_Comm_size(MPI_COMM_WORLD, &sz);
  MPI_Comm_rank ( MPI_COMM_WORLD, &rnk );  
  chunk = n / sz; 
  double start = omp_get_wtime();
  MPI_Scatter(buff,chunk,MPI_DOUBLE, x,chunk,MPI_DOUBLE, 0,MPI_COMM_WORLD);
  MPI_Scatter(&buff[n],chunk,MPI_DOUBLE, y,chunk,MPI_DOUBLE,0,MPI_COMM_WORLD);
  for (i=0; i<chunk; i++){  
     x[i] = x[i] + y[i];
  }
  MPI_Gather(x,chunk,MPI_DOUBLE, buff,chunk,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Finalize(); 
  double end = omp_get_wtime();
  printf("\nTime = %f\n",end - start);
  return 0;
}
