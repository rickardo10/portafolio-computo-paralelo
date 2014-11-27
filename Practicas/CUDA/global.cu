#include <stdio.h>
#include <stdlib.h> 
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

//__constant__ int datos[1024];

__global__ void kernel(int *d_dst, int *d_src) {
  int tId = threadIdx.x + blockIdx.x * blockDim.x;
  d_dst[tId] = d_src[tId];
}

int main(int argc, char **argv) {

  int *d_datos, *h_datos, *d_src;
  cudaMalloc((void**)&d_datos, sizeof(int) * 1024);
  cudaMalloc((void**)&d_src, sizeof(int) * 1024);
  h_datos = (int *)malloc(sizeof(int) * 1024);
  
  int *test = new int[1024];

  memset(test, 0, sizeof(int) * 1024);

  for (int i = 0; i < 1024; i++) {
    test[i] = i;
  }
 
  //GPU Time
  cudaEvent_t start, stop;
  float time;

  cudaMemcpy(d_src, d_datos, sizeof(int)*1024, cudaMemcpyHostToDevice);

  cudaEventCreate(&start); 
  cudaEventCreate(&stop);
  cudaEventRecord(start,0);

  // Kernel call
  kernel<<< 1, 1024 >>>(d_datos, d_src);
 
  cudaEventRecord(stop,0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&time, start, stop);

  // Copying From Device to Host
  cudaMemcpy(h_datos, d_datos, sizeof(int)*1024, cudaMemcpyDeviceToHost);
   for (int i = 0; i < 1024; i++)
     printf("\n %d", h_datos[i]); 

   printf("\t Time : %f ms\n",time);

  cudaEventDestroy(start);
  cudaEventDestroy(stop); 
  free(test);
  cudaFree(d_datos); 

  return 0;
}