# Introducción

Le comparto mis resultados del código en openMP. En el archivo "resultados.txt" le comparto la impresión de pantalla que me arroja el código.

En el código vienen 3 funciones: 
	1) ejercicio_6.
	2) ejercicio_7.
	3) ejercicio_8. 

En cada una de esas funciones vienen los pasos que se necesitan realizar para ejecutar el código. En este momento se ejecuta el código utilizando matrices cuatradas con un sólo valor, ya que es la manera más sencilla de crear matrices rápidamente y verificar el resultado. El procedimiento que realicé es paralelizar el producto punto y en la multiplicación Matriz-Vector y Matriz-Matriz se manda llamar por cada celda que se requiere el resultado. 

En el código para la multiplicación Matriz-Vector y Matriz-Matriz no aparece ningún #pragma, porque no se paraleliza nada en esa parte. La parte de la paralelización está en el producto punto ya que considero que es el punto crítico que debe ser paralelizado, después, esa función es llamada en la multiplicación Matriz-Vector y Matriz-Matriz, convirtiendo así, estas funciones, en funciones paralelas.

# Ejecución

```bash
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

