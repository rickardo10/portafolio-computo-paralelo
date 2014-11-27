#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[]){

  int rnk, sz, n, I, info, i, chunk;

  double *x, *y, *buff;

  n = atoi(argv[1]);

  // Initializing Arrays
  x = (double*)malloc(n*sizeof(double));
  y = (double*)malloc(n*sizeof(double));
  buff = (double*)malloc(n*sizeof(double));

  /* Initialize threaded MPI environment */
  MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &info);
  MPI_Comm_size(MPI_COMM_WORLD, &sz); /* Find out how many MPI procs */
  MPI_Comm_rank ( MPI_COMM_WORLD, &rnk );  

  chunk = n / sz; /* Assume sz divides n exactly */

  MPI_Scatter(buff,chunk,MPI_DOUBLE, x,chunk,MPI_DOUBLE, 0,MPI_COMM_WORLD);
  MPI_Scatter(&buff[n],chunk,MPI_DOUBLE, y,chunk,MPI_DOUBLE,0,MPI_COMM_WORLD);

  double start = omp_get_wtime();

  for (i=0; i<chunk; i++)  
     x[i] = x[i] + y[i];
    
  printf("\n%d operations were run on processor: %d\n", chunk, rnk);


  MPI_Gather(x,chunk,MPI_DOUBLE, buff,chunk,MPI_DOUBLE,0,MPI_COMM_WORLD);

  MPI_Finalize(); 

  double end = omp_get_wtime();
  printf("\nExecution Time = %f\n",end - start);

  return 0;
}
