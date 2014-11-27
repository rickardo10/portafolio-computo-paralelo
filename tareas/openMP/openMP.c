#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

double* Suma_Vec(double *a, double *b, int size);
double dot( double *a, double *b, int size);
double* init_vec(int size, int mult);
double** Mat_Mat(double **a, double **b, int m, int n);
double** init_mat(int m, int n, int mult);
double* column_extract(int m, double **a, int col);
double* Mat_Vec(double **a, double *b, int m, int n);
void print_vec(double *a, int size);
void print_mat(double **a, int m, int n);

void ejercicio_6(void){
    printf("Se efectua el producto punto C = A * B donde,\n");
    int size = 6;
    double *a = init_vec(size, 3);
    double *b = init_vec(size, 5);
    double c = dot(a,b,size);
    printf("A =\n");
    print_vec(a,size);
    printf("B =\n");
    print_vec(b,size);
    printf("C =\n");
    printf("%f\n",c);
    printf("\n");
}

void ejercicio_7(void){
    printf("Se efectuará la multiplicación entre Matriz y Vector Y = A * x donde,\n");
    int size = 6;
    double **A = init_mat(size, size, 3);
    double *x = init_vec(size, 4);
    double *Y = Mat_Vec(A,x,size,size);
    printf("A =\n");
    print_mat(A,size,size);
    printf("x =\n");
    print_vec(x,size);
    printf("Y =\n");
    print_vec(Y,size);
}

void ejercicio_8(void){
    printf("Se efectuará la multiplicación entre Matriz y Matriz Y = A * B donde, \n");
    int size =  6;
    double **A = init_mat(size, size, 3);
    double **B = init_mat(size, size, 8);
    double **Y = Mat_Mat(A,B,size,size);
    printf("A =\n");
    print_mat(A,size,size);
    printf("B =\n");
    print_mat(B,size, size);
    printf("Y =\n");
    print_mat(Y,size,size);
}

int main(int argc, char *argv[]){
    ejercicio_6();
    ejercicio_7();
    ejercicio_8();
    return 0;
}

double* Suma_Vec(double *a, double *b, int size){
    int i = 0;
    double *c;
    c = (double*) malloc(size*sizeof(double));
#pragma omp parallel for
    for( i = 0; i < size; ++i){
        c[i] = a[i] + b[i];
    }
    return c;
}

double dot( double *a, double *b, int size){
    double sum = 0;
    int i = 0;
#pragma omp parallel for reduction(+:sum)
    for( i = 0; i < size; ++i){
        sum += a[i] * b[i];
    }
    return sum;
}

double** Mat_Mat(double **a, double **b, int m, int n){
    double **c;
    c = init_mat( m, n, -1 );
    int i = 0; int j = 0;
    for( i = 0; i < m; i++){
        for( j = 0; j < n; j++){
            c[i][j] = dot(a[i], column_extract(m, b, j), m);
        }
    }
    return c;
}

double* Mat_Vec(double **a, double *b, int m, int n){
    double *c;
    c = init_vec(n,-1 );
    int i = 0;
    for( i = 0; i < m; i++){
        c[i] = dot(a[i], b, n);
    }
    return c;
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

double** init_mat(int m, int n, int mult){
    int i = 0; int j = 0; double **a;
    a = (double**)malloc(m*sizeof(double*));
    for(i = 0; i < m; i++){
        a[i] = (double*)malloc(n*sizeof(double));
    }

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            a[i][j] = mult;
        }
    }
    return a;
}

double* column_extract(int m, double **a, int col){
    double *c;
    c = (double*)malloc(m*sizeof(double));
    int i = 0;
    for( i = 0; i < m; i++){
        c[i] = a[i][col];
    }
    return c;
}

void print_vec(double *a, int size){
    int i = 0;
    for(i = 0; i < size; i++){
        printf("%f ", a[i]);
    }
    printf("\n");
}

void print_mat(double **a, int m, int n){
    int i = 0; int j = 0;
    for( i = 0; i < m; i++){
        for( j = 0; j < n; j++){
            printf("%f ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}                                                                          