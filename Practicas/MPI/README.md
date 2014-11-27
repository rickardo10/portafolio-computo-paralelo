Ejercicios de MPI
=================

Introducción
------------

En esta sección se presentan algunos ejercicios utilizando MPI. A continuación se describirán cada uno de los incisos, el código que se utilizó, y el resultado arrojado por el programa.

### Ejercicios

* Iniciando MPI. Hola Mundo con MPI. Código utilizado: hello.c

```
[rocampo@rocampo MPI]$ mpicc hello.c -o hello
[rocampo@rocampo MPI]$ mpirun hello
Hello world
Hello world
```

* Hola mundo desde el procesador, rango, total de procesos y nombre del procesador. Código utilizado: hello_processors.c

```
[rocampo@rocampo MPI]$ mpicc hello_processors.c -o hello
[rocampo@rocampo MPI]$ mpirun hello
Hola Mundo!!! desde el procesador rocampo, rank 0 out of 2 processors
Hola Mundo!!! desde el procesador rocampo, rank 1 out of 2 processors
```

* Envío y Recepción de un número entre dos procesos (Bloqueante). Código utilizado: bloqueante.c

```
[rocampo@rocampo MPI]$ mpirun hello
Process 1 received number -1 from process 0
```

* Envío y Recepción de un número entre dos procesos de forma No bloqueante. Código utilizado: no-bloqueante.c

```
[rocampo@rocampo MPI]$ mpicc no-bloqueante.c -o hello
[rocampo@rocampo MPI]$ mpirun hello
Among 2 processes, process 0 received from right neighbor: 1
Among 2 processes, process 1 received from right neighbor: 0
```

* Ping-Pong. Probarlo con 2 y 4 procesos y obtener el tiempo de procesamiento en cada uno de ellos con MPI_Wtime().

```
[rocampo@rocampo MPI]$ mpicc ping-pong.c -o hello
[rocampo@rocampo MPI]$ mpirun -np 3 hello 10
0 2 hello
n is 10
n is 10
n is 10
10 multiply-adds in 0.000855923 seconds,  for an average time of 3.42369e-09
10 ping-pongs in 2.19345e-05 seconds,  for an average message time of 1.09673e-06
10 ping-pongs in 0.00366402 seconds,  for an average message time of 7.32803e-10
```

* Qué hacen las funciones:
    *   *MPI_Scatter*: Envía datos de un proceso a todos los demás procesos en un comunicador.
    *   *MPI_Gather*: Reune los valores de un grupo de procesos.
    *   *MPI_Allreduce*: Combina los valores de todos los procesos y distribuye el resultado a todos los procesos.
    *   *MPI_Allgather*: Reune los datos de todas las tareas y distribuye los datos combinados a todas las tareas.
    *   *MPI_Barrier*: Bloquea hasta que todos los procesos en el comunicador han alcanzado la rutina.
    *   *MPI_Reduce*: Reduce los valores en todos los procesos a un solo valor.

* Calcular la suma de números de un arreglo unidimensional utilizando MPI_Scatter y MPI_Gather. Código utilizado: sum_array.c

```
[rocampo@rocampo MPI]$ mpicc sum_array.c -o hello
[rocampo@rocampo MPI]$ mpirun hello
Execution Time: 0.000638 
```

* Puedes calcular la suma de números del ejemplo 7 utilizando la función MPI_Reduce para obtener el resultado. Código utilizado: sum_array_reduce.c

```
[rocampo@rocampo MPI]$ mpicc sum_array_reduce.c -o hello
[rocampo@rocampo MPI]$ mpirun hello
Execution Time: 0.000354 
```
