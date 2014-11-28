Ejercicios de OpenMP
====================

Introducción
------------

En esta sección se presentan algunos ejercicios utilizando OpenMP. A continuación se describirán cada uno de los incisos, el código que se utilizó, y el resultado arrojado por el programa.

Ejercicios
----------

* Versión instalada de OpenMP. Código utilizado: version.c

```
[rocampo@rocampo OpenMP]$ gcc -fopenmp -o version version.c
[rocampo@rocampo OpenMP]$ ./version
Este  es nuestro primer ejemplo en openMP

Hola mundo

Hola mundo

Hola mundo

Hola mundo

Hola mundo

Hola mundo

Hola mundo

Hola mundo

La version instalada de OpenMP es: 201307
```

* Número de cores disponibles en el equipo, ID actual y número total de threads. Código utilizado: cores.c

```
[rocampo@rocampo OpenMP]$ gcc -fopenmp cores.c
[rocampo@rocampo OpenMP]$ ./a.out
Este es nuestro segundo ejemplo en openMP
3:hello multicore user! I am thread 3 out of 8
7:hello multicore user! I am thread 7 out of 8
4:hello multicore user! I am thread 4 out of 8
6:hello multicore user! I am thread 6 out of 8
2:hello multicore user! I am thread 2 out of 8
5:hello multicore user! I am thread 5 out of 8
1:hello multicore user! I am thread 1 out of 8
0 : NCPU    = 8
0 : NTHR    = 8
0 : NPR     = 8
0:hello multicore user! I am thread 0 out of 8
```

* Suma de vectores en paralelo. Código utilizado: sum_vec.c

```
[rocampo@rocampo OpenMP]$ gcc -fopenmp sum_vec_sec.c
[rocampo@rocampo OpenMP]$ ./a.out 100000000
Time = 0.362933
```

* Suma de vectores en secuencial. Código utilizado: sum_vec_sec.c

```
[rocampo@rocampo OpenMP]$ gcc -fopenmp sum_vec.c
[rocampo@rocampo OpenMP]$ ./a.out 100000000
Time = 0.287442
```

* Probar el código de suma de vectores com más threads que cores existen en la computadora. Código utilizado: sum_vec.c

```
[rocampo@rocampo OpenMP]$ gcc -fopenmp sum_vec.c
[rocampo@rocampo OpenMP]$ ./a.out
Time = 0.352524
```

* Reducir el problema de Matriz Punto. Código utilizado: openMP.c

```
Have a nice day!
r.ocampo@10.40.53.1's password:
Last login: Fri Sep 19 22:27:55 2014 from 10.40.127.201
(virPy3)[r.ocampo@turing ~]$ ls
openMP  Thesis  virPy3
(virPy3)[r.ocampo@turing ~]$ cd openMP/
(virPy3)[r.ocampo@turing openMP]$ ./test
Se efectua el producto punto C = A * B donde,
A =
0.000000 3.000000 6.000000 9.000000 12.000000 15.000000
B =
0.000000 5.000000 10.000000 15.000000 20.000000 25.000000
C =
825.000000
```

* Multiplicación Matriz-Vector. Código utilizado: openMP.c

```
Se efectuará la multiplicación entre Matriz y Vector Y = A * x donde,

A =
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000

x =
0.000000 4.000000 8.000000 12.000000 16.000000 20.000000

Y =
180.000000 180.000000 180.000000 180.000000 180.000000 180.000000
```

* Multiplicación de matriz-matriz. Código utilizado: openMP.c

```
Se efectuará la multiplicación entre Matriz y Matriz Y = A * B donde,

A =
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000
3.000000 3.000000 3.000000 3.000000 3.000000 3.000000

B =
8.000000 8.000000 8.000000 8.000000 8.000000 8.000000
8.000000 8.000000 8.000000 8.000000 8.000000 8.000000
8.000000 8.000000 8.000000 8.000000 8.000000 8.000000
8.000000 8.000000 8.000000 8.000000 8.000000 8.000000
8.000000 8.000000 8.000000 8.000000 8.000000 8.000000
8.000000 8.000000 8.000000 8.000000 8.000000 8.000000

Y =
144.000000 144.000000 144.000000 144.000000 144.000000 144.000000
144.000000 144.000000 144.000000 144.000000 144.000000 144.000000
144.000000 144.000000 144.000000 144.000000 144.000000 144.000000
144.000000 144.000000 144.000000 144.000000 144.000000 144.000000
144.000000 144.000000 144.000000 144.000000 144.000000 144.000000
144.000000 144.000000 144.000000 144.000000 144.000000 144.000000
```
