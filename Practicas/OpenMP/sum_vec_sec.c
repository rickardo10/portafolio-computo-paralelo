#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void Sum_Vec(double* a, double* b, double* c, int size)
{
  int i = 0;
  for (i = 0; i < size; ++i)
      c[i] = a[i] + b[i];
}

double* init_vec(int size, int mult){
    int i = 0; double *a;
    a = (double*)malloc(size*sizeof(double));
    a[0] = 0;
    for( i = 1; i < size; i++){
        a[i] = a[i-1] + mult;
    }
    return a;
}

int main(){
  int size = 100000000; 
  double *a = init_vec(size, 3);
  double *b = init_vec(size, 5);
  double *c = init_vec(size, 0);
  double start = omp_get_wtime();
  Sum_Vec(a, b, c, size);
  double end = omp_get_wtime();
  printf("Time = %f\n",end - start);
  return 0;
}
