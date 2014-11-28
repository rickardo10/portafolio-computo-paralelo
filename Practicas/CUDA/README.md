Ejercicios de CUDA
==================

Introducción
------------

En esta sección se presentan algunos ejercicios de CUDA. A continuación se describirán cada uno de los incisos, el código que se utilizó y el resultado arrojado por el programa.

Ejercicios
----------

* Se describen las propiedades de la GPU. Código utilizado: propiedades.cu

```
[rocampo@rocampo CUDA]$ nvcc propiedades.cu
[rocampo@rocampo CUDA]$ ./a.out
Total Device found: 1
**************************************
Device Name      - GeForce GTX 770M 
**************************************
Total Global Memory      -> 3137436 KB
Shared memory available per block    -> 48 KB
Number of registers per thread block     -> 65536
Warp size in threads     -> 32
Memory Pitch     -> 2147483647 bytes
Maximum threads per block    -> 1024
Maximum Thread Dimension (block)     -> 1024 1024 64
Maximum Thread Dimension (grid)      -> 2147483647 65535 65535
Total constant memory    -> 65536 bytes
CUDA ver     -> 3.0
Clock rate   -> 797000 KHz
Texture Alignment    -> 512 bytes
Device Overlap   -> Allowed
Number of Multi processors   -> 5
```

* Se realiza una suma de vectores con CUDA. Código utilizado: addition.cu

```
[rocampo@rocampo CUDA]$ nvcc addition.cu 1000
[rocampo@rocampo CUDA]$ ./a.out
Time : 0.027648 ms
```

* Se realiza una suma de vectores con CUDA, aprovechando la memoria compartida. Código utilizado: addition_shared.cu

```
[rocampo@rocampo CUDA]$ nvcc addition_shared.cu
[rocampo@rocampo CUDA]$ ./a.out
Time : 0.033760 ms
```

* Se realiza una multiplicación de matrices con CUDA. Código utilizado: mult.cu

```
[rocampo@rocampo CUDA]$ nvcc mult.cu
[rocampo@rocampo CUDA]$ ./a.out 1000
Time : 64.617027 ms
```

* Se realiza una multiplicación de matrices con el CPU. Código utilizado: mult_secuential.c

```
[rocampo@rocampo CUDA]$ gcc -fopenmp mult_secuential.c
[rocampo@rocampo CUDA]$ ./a.out 1000
Time = 5129.29 ms
```

* Se compara la diferencia de tiempo entre un proceso que utiliza memoria constante y otro que utiliza memoria global. Código utilizado: constant.cu, global.cu

```
[rocampo@rocampo CUDA]$ nvcc constant.cu
[rocampo@rocampo CUDA]$ ./a.out
Time : 0.028320 ms
[rocampo@rocampo CUDA]$ nvcc global.cu
[rocampo@rocampo CUDA]$ ./a.out
Time : 0.010976 ms
```
