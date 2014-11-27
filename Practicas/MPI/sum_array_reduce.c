#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define master 0

int main(int argc,char *argv[]){
    float *array;
	int count;
	int size,mysize,i,k,j;
    float sum;
	double start, end;
    int n,id,err;        
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &n);  
    start = MPI_Wtime();
    size = 100000;
    count = size/n;  
	array=(float*)malloc(count*sizeof(float));
    for(i=0; i<count; i++)
	    array[i] = i; 
    sum = 0;
	for (i = 0; i < count; i++) {
	  sum += array[i];
	}
	float global_sum;
	MPI_Reduce(&sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0,
		   MPI_COMM_WORLD);
	if(id == master){
        end = MPI_Wtime(); 
        printf("Time: %f \n\n", end - start);  
	}
    MPI_Barrier(MPI_COMM_WORLD); 
    err = MPI_Finalize();
}
