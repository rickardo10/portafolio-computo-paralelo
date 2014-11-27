#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int n,id,err;
#define master 0

void init_it(int  *argc, char ***argv);
void init_it(int  *argc, char ***argv) {
	err = MPI_Init(argc,argv);
    err = MPI_Comm_size( MPI_COMM_WORLD, &n );
    err = MPI_Comm_rank(MPI_COMM_WORLD, &id);
}
int main(int argc,char *argv[]){
	int *myray,*send_ray,*back_ray;
	int count;
	int size,mysize,i,k,j,total;
	double start, end;
	init_it(&argc,&argv);
    start = MPI_Wtime();
    size = 100000;
	count=size/n;
	myray=(int*)malloc(count*sizeof(int));
	if(id == master){
		send_ray=(int*)malloc(size*sizeof(int));
		back_ray=(int*)malloc(n*sizeof(int));
		for(i=0;i<size;i++)
			send_ray[i]=i;
		}
	err = MPI_Scatter(	send_ray, count,   MPI_INT,
						    myray,    count,   MPI_INT,
	                 	    master,
	                 	    MPI_COMM_WORLD);
	total=0;
	for(i=0;i<count;i++)
	    total=total+myray[i];
	printf("id= %d total= %d\n ",id,total);
    err = MPI_Gather(&total,    1,  MPI_INT, 
						back_ray, 1,  MPI_INT, 
	                 	master,                  
	                 	MPI_COMM_WORLD);
	if(id == master){
	  total=0;
	  for(i=0;i<n;i++)
	    total=total+back_ray[i];
          end = MPI_Wtime(); 
          printf("Time: %f \n\n", end - start);  
	}
    err = MPI_Finalize();
}
