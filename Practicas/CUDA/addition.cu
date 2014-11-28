#include<stdio.h>
#define N 1000

__global__ void addvec(int *a, int *b, int *c)
{
 int tid=blockIdx.x; //manejar los datos a este índice
 if(tid<N)
   c[tid]=a[tid]+b[tid];
}

//función principal
int main(void){
  int a[N], b[N], c[N];
  int *dev_a, *dev_b, *dev_c;

  //asignar memoria en la GPU
  cudaMalloc((void**)&dev_a,N*sizeof(int));
  cudaMalloc((void**)&dev_b,N*sizeof(int));
  cudaMalloc((void**)&dev_c,N*sizeof(int));

  //Llenar datos a los arreglos 'a' y 'b' en la CPU
  for(int i=0; i<N;i++){
    a[i]=i;
    b[i]=i+1;
  }

  //GPU Time
  cudaEvent_t start, stop;
  float time;

  //copiar el arreglo 'a' y 'b' en la GPU
  cudaMemcpy(dev_a,a,N*sizeof(int),cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b,b,N*sizeof(int),cudaMemcpyHostToDevice);

  cudaEventCreate(&start); 
  cudaEventCreate(&stop);
  cudaEventRecord(start,0);

  //lanzar el kernel
  addvec<<<N,1>>>(dev_a,dev_b,dev_c);

  cudaEventRecord(stop,0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&time, start, stop);
	
  printf("Time : %f ms\n",time);

  //copiar el arreglo 'c' de la GPU a la CPU
  cudaMemcpy(c,dev_c,N*sizeof(int),cudaMemcpyDeviceToHost);

  cudaFree(dev_a);
  cudaFree(dev_b);
  cudaFree(dev_c);
  return 0;
  
} 
