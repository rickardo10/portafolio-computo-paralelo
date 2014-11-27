#include <stdio.h>
#include <stdlib.h> 
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#define BLOCK_SIZE 16


// Matrixes Multiplcation (Global Memory)
__global__ void multiply_gm(float *C,float *A,float *B, int nrow,int ncol)
{
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  int idy = blockIdx.y * blockDim.y + threadIdx.y;

  int index=idy*ncol+idx;

  if (idy<nrow && idx<ncol){
    float sum=0.0f;
    for(int k=0;k<ncol;k++){
      sum+=A[idy*ncol+k]*B[k*ncol+idx];
    }	
    C[index] = sum;
  }	
}

int div_up(int a,int b){
  return(a/b + (a%b == 0 ? 0:1));
}

int main(int argc, char* argv[]){
  float *A_h,*B_h,*C_h; // Host matrixes
  float *A_d,*B_d,*C_d;  //Device matrixes
  int nrow = atoi(argv[1]);  // rows
  int ncol = nrow;  // cols
  float N=nrow*ncol;  // number of elements

  //GPU Time
  cudaEvent_t start, stop;
  float time;
	
  size_t size=N * sizeof(float);

  A_h = (float *)malloc(size); 
  B_h = (float *)malloc(size);
  C_h = (float *)malloc(size);

  //Initializing Host matrixes
  for (int i=0; i<nrow; i++){
    for(int j=0;j<ncol;j++){
      A_h[i*ncol+j] = 1.0f;
      B_h[i*ncol+j] = 2.0f;	
      //A_h[i*ncol+j] = rand()/100.0f;
      //B_h[i*ncol+j] = rand()/100.0f;	
    }
  }

  /*
  printf("\nMatrix A:\n");
  for (int i=0; i<nrow; i++){
    for(int j=0;j<ncol;j++){
      printf("%.2f ", A_h[i*ncol+j]);
    }
    printf("\n");
  }
  printf("\n\nMatrix B:\n");
  for (int i=0; i<nrow; i++){
    for(int j=0;j<ncol;j++){
      printf("%.2f ", B_h[i*ncol+j]);
    }
    printf("\n");
  }
  */

  cudaMalloc((void **) &A_d,size);
  cudaMalloc((void **) &B_d,size);
  cudaMalloc((void **) &C_d,size);

  // Host to Device transfer
  cudaMemcpy(A_d, A_h, size, cudaMemcpyHostToDevice);
  cudaMemcpy(B_d, B_h, size, cudaMemcpyHostToDevice);

  //Realizamos el cálculo en el Device
  dim3 block_size(BLOCK_SIZE,BLOCK_SIZE);
  dim3 n_blocks(div_up(ncol,block_size.x),div_up(nrow,block_size.y)) ;

  cudaEventCreate(&start); 
  cudaEventCreate(&stop);
  cudaEventRecord(start,0);

  multiply_gm<<< n_blocks, block_size >>> (C_d,A_d,B_d,nrow,ncol);
	
  cudaEventRecord(stop,0);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&time, start, stop);
  printf("\t Time : %f ms\n",time);

  // Result from Device to Host
  cudaMemcpy(C_h, C_d, size,cudaMemcpyDeviceToHost);

  /*
  //Results
  printf("\n\nMatrix C:\n");
  for (int i=0; i<nrow; i++){
    for(int j=0;j<ncol;j++){
      printf("%.2f ", C_h[i*ncol+j]);
    }
    printf("\n");
  }
  */

  system("sleep 1");
	
  free(A_h); 
  free(B_h); 
  free(C_h); 

  cudaFree(A_d); 
  cudaFree(B_d); 
  cudaFree(C_d); 
  return 0;
}