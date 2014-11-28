#include <omp.h>
#include <stdio.h>
int main(){
  printf("Este es nuestro segundo ejemplo en openMP\n");
#pragma omp parallel
  {
    //Initializing Parallel Region
    int NCPU,tid,NPR,NTHR;
    NCPU=omp_get_num_procs();    //get the number of available cores
    tid=omp_get_thread_num();    //get current thread ID
    NPR=omp_get_num_threads();   //get total number of threads
    NTHR=omp_get_max_threads();  //get number of threads requested
    if(tid==0)
      {
	printf("%i : NCPU\t= %i\n",tid,NCPU);
	printf("%i : NTHR\t= %i\n",tid,NTHR);
	printf("%i : NPR \t= %i\n",tid,NPR);
      }
    printf("%i:hello multicore user! I am thread %i out of %i\n",tid,tid,NPR);
  }
  return 0;
}
