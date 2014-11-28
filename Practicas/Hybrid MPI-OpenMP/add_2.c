#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0

int main (int argc, char *argv[]) 
{
	int *a, *b, *c;
	int total_proc, rank, T;
	long long int n_per_proc, i, n;
	MPI_Status status;
	MPI_Init (&argc, &argv);
	MPI_Comm_size (MPI_COMM_WORLD, &total_proc);
	MPI_Comm_rank (MPI_COMM_WORLD,&rank);
    int * ap, *bp, *cp;	
	if (rank == MASTER)
	{
		scanf ("%d", &T);
		MPI_Bcast (&T, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    	while (T--){  	
  			scanf ("%lld", &n);
				a = (int *) malloc(sizeof(int)*n);
       	b = (int *) malloc(sizeof(int)*n);
       	c = (int *) malloc(sizeof(int)*n);
				MPI_Bcast (&n, 1, MPI_LONG_LONG_INT, MASTER, MPI_COMM_WORLD);
     		n_per_proc = n/total_proc;
			for(i=0;i<n;i++){
				scanf ("%d", &a[i]);
    	}
			for(i=0;i<n;i++){
				scanf ("%d", &b[i]); 
    	}
			if(n%total_proc != 0){
      	n_per_proc+=1;
    		for(i=0;i<(n_per_proc*total_proc - n);i++){
      	 	a[n+i] = 0;
      		b[n+i] = 0;
      	}
			}
			ap = (int *) malloc(sizeof(int)*n_per_proc);
			bp = (int *) malloc(sizeof(int)*n_per_proc);
			cp = (int *) malloc(sizeof(int)*n_per_proc);
  		double start = omp_get_wtime();
			MPI_Bcast (&n_per_proc, 1, MPI_LONG_LONG_INT, MASTER, MPI_COMM_WORLD);
			MPI_Scatter(a, n_per_proc, MPI_INT, ap, n_per_proc, MPI_INT, 0, MPI_COMM_WORLD); 
			MPI_Scatter(b, n_per_proc, MPI_INT, bp, n_per_proc, MPI_INT, 0, MPI_COMM_WORLD); 
			for(i=0;i<n_per_proc;i++){
				cp[i] = ap[i]+bp[i];
      }
			MPI_Gather(cp, n_per_proc, MPI_INT, c, n_per_proc, MPI_INT, MASTER, MPI_COMM_WORLD);
		}
    } else { 
		MPI_Bcast (&T, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
		while (T--) {
			MPI_Bcast (&n, 1, MPI_LONG_LONG_INT, MASTER, MPI_COMM_WORLD);
			MPI_Bcast (&n_per_proc, 1, MPI_LONG_LONG_INT, MASTER, MPI_COMM_WORLD);
			ap = (int *) malloc(sizeof(int)*n_per_proc);
			bp = (int *) malloc(sizeof(int)*n_per_proc);
			cp = (int *) malloc(sizeof(int)*n_per_proc);
			MPI_Scatter(a, n_per_proc, MPI_INT, ap, n_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
			MPI_Scatter(b, n_per_proc, MPI_INT, bp, n_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
			for(i=0;i<n_per_proc;i++){
				cp[i] = ap[i]+bp[i];		
			}
			MPI_Gather(cp, n_per_proc, MPI_INT, c, n_per_proc, MPI_INT, MASTER, MPI_COMM_WORLD);
        }
	}
	MPI_Finalize();
	double end = omp_get_wtime();
	printf("\nTime = %f\n",end - start);
	return 0;
}
