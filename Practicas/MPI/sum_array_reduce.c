#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define mpi_root 0
/* end globals  */

int main(int argc,char *argv[]){

        float *myray;
	int count;
	int size,mysize,i,k,j;
        float local_sum;
	double start, end;
        int numnodes,myid,mpi_err;        

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numnodes);  
                
        start = MPI_Wtime();

        size = 100000;
        count = size/numnodes;  
	myray=(float*)malloc(count*sizeof(float));
        for(i=0; i<count; i++)
	  myray[i] = i; 
        
	                
/* each processor does a local sum */

        local_sum = 0;
	for (i = 0; i < count; i++) {
	  local_sum += myray[i];
	}
        printf("myid= %d total= %f\n ",myid,local_sum);

	// Reduce all of the local sums into the global sum
	float global_sum;
	MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0,
		   MPI_COMM_WORLD);


/* the root prints the global sum */
	if(myid == mpi_root){
          end = MPI_Wtime(); 
	  printf("results from all processors= %f \n ",global_sum);
          printf("Execution Time: %f \n\n", end - start);  
	}

    MPI_Barrier(MPI_COMM_WORLD); 
    mpi_err = MPI_Finalize();
}
