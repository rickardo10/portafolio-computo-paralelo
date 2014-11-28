Ejercicios de OpenMP+MPI
========================

Introducción
------------

En esta sección se presentan algunos ejercicios combinando herramientas de MPI y OpenMP. A continuación se describirán cada uno de los incisos, el código que se utilizó y el resultado arrojado por el programa.

Ejercicios
----------

* Probar el primer ejemplo con los hilos y procesos por default de la computadora. Código utilizado: hello.c

```
[rocampo@rocampo Hybrid MPI-OpenMP]$ mpicc hello.c -fopenmp
[rocampo@rocampo Hybrid MPI-OpenMP]$ mpirun a.out
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 0 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 0 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 1 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 2 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 2 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 3 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 3 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 1 de un total de 4 procesos en rocampo
```

* Probar el primer ejemplo con cuatro hilos y dos procesos. Código utilizado: hello.c

```
[rocampo@rocampo Hybrid MPI-OpenMP]$ mpirun -np 2 a.out
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 0 de un total de 2 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 0 de un total de 2 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 1 de un total de 2 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 1 de un total de 2 procesos en rocampo
```

* Probar el primer ejemplo con cuatro hilos y cuatro procesos. Código utilizado: hello.c

```
[rocampo@rocampo Hybrid MPI-OpenMP]$ mpirun -np 4 a.out
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 1 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 2 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 2 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 3 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 3 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 0 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 0 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 1 de un total de 4 procesos en rocampo
```

* Probar el primer ejemplo con dos hilos y cuatro procesos. Código utilizado: hello.c

```
[rocampo@rocampo Hybrid MPI-OpenMP]$ mpirun -np 4 a.out
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 1 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 2 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 2 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 3 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 3 de un total de 4 procesos en rocampo
Hola... Desde el hilo 0 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 0 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 0 de un total de 4 procesos en rocampo
Hola... Desde el hilo 1 de un total de 2 procesadores (hilos) ejecutado dentro del proceso 1 de un total de 4 procesos en rocampo
```

* Realizar la suma de dos vectores utilizando OpenMP y MPI con dos estrategias de solución. Compara el tiempo de ejecucuón de las dos estrategias. Código utilizado: add_1.c, add_2.c

```
[rocampo@rocampo Hybrid MPI-OpenMP]$ mpirun  a.out 100000000

Time = 0.757592

Time = 0.757794

Time = 0.757795

Time = 0.757812
```

* Realizar el ordenamiento de una matriz de N elementos por el método de burbuja con OpenMP y MPI. Código utilizado: buble.c

```
[rocampo@rocampo Hybrid MPI-OpenMP]$ mpicc -fopenmp buble.c
[rocampo@rocampo Hybrid MPI-OpenMP]$ mpirun a.out 12
Input Array for Sorting 
2044897763   1967513926   1365180540   1540383426   304089172   1303455736   35005211   521595368   294702567   1726956429   336465782   861021530   



Number of Elements to be sorted : 12 
Sorted output sequence is
35005211   294702567   304089172   336465782   521595368   861021530   1303455736   1365180540   1540383426   1726956429   1967513926   2044897763   
```
