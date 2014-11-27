#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  int my_rank, ncpus;
  int left_neighbor, right_neighbor;
  int data_received=-1;
  int tag = 101;
  MPI_Status statSend, statRecv;
  MPI_Request reqSend, reqRecv;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &ncpus);

  left_neighbor = (my_rank-1 + ncpus)%ncpus;
  right_neighbor = (my_rank+1)%ncpus;

  MPI_Isend(&my_rank,1,MPI_INT,left_neighbor,tag,MPI_COMM_WORLD,&reqSend); // comm start
  MPI_Irecv(&data_received,1,MPI_INT,right_neighbor,tag,MPI_COMM_WORLD,&reqRecv);

  // maybe do something useful here

  MPI_Wait(&reqSend, &statSend); // complete comm
  MPI_Wait(&reqRecv, &statRecv);
   
  printf("Among %d processes, process %d received from right neighbor: %d\n",
	 ncpus, my_rank, data_received);

  // clean up
  MPI_Finalize();
  return 0;
}
