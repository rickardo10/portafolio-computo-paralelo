#include<stdio.h>
#define N 10

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

  //copiar el arreglo 'a' y 'b' en la GPU
  cudaMemcpy(dev_a,a,N*sizeof(int),cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b,b,N*sizeof(int),cudaMemcpyHostToDevice);

  //lanzar el kernel
  addvec<<<N,1>>>(dev_a,dev_b,dev_c);

  //copiar el arreglo 'c' de la GPU a la CPU
  cudaMemcpy(c,dev_c,N*sizeof(int),cudaMemcpyDeviceToHost);

  //Desplegar el resultado
  for(int i=0; i<N; i++){
    printf("%d+%d=%d\n",a[i],b[i],c[i]);
  }
  cudaFree(dev_a);
  cudaFree(dev_b);
  cudaFree(dev_c);
  return 0;
  
} 