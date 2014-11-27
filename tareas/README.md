**Sincronización:** Un algoritmo paralelo sincronizado es aquel que tiene un proceso tal que en alguna etapa del proceso, no es activado hasta que otro proceso ha finalizado una porción del programa. El tiempo puede ser alcanzado por usar diferentes primitivos de sincronización.

**Granularidad:** Es una medida cualitativa de la relación que existe entre la computación y la comunicación. Los periodos de computación son separados por periodos de comunicación por eventos de sincronización.

Existen dos tipos de granularidad:

	1. Paralelismo de grano fino: 
		a. Pequeñas cantidades de trabajo computacional son hechas entre eventos de comunicación.
		b. Relación computación-comunicación bajo.
		c. Facilidad de balancear cargas.
		d. Implica una sobrecarga alta de comunicación y menor oportunidad de mejora en rendimiento.
		e. Si la granularidad es muy fina puede provocar que el tiempo de comunicación sea mayor al proceso.
	2. Paralelismo de grano grueso:
		a. Grandes cantidades de trabajo computacional en comparación con los eventos de comunicación y sincronización.
		b. Relación computación-comunicación alta.
		c. Implica mayor oportunidad de mejorar el rendimiento.
		d. Más difícil de balancear las cargas.

**Speed-up observado:** Es una de los indicadores de rendimiento de un programa de paralelismo. Es simple y ampliamente usado. El sepeedup de un códico que ha sido paralelizado está dado por:

**Paralelismo masivo:** Se refiere al hardware que compone un sistema paralelo, tiene muchos procesadores. Una computadora con estas características está compuesta por cientos de miles de procesadores intercomunicados.

**Escalabilidad:** Se refiere a la habilidad de un sistema paralelo (Hardware y/o Software) para demostrar un incremento proporcional en la velocidad con la adición de más recursos. Los factores que contribuyen a la escalabilidad son:
	1. Hardware: Memoria-CPU propiedades de comunicación y bandas.
	2. Algoritmo de aplicación.
	3. Sobrecarga de paralelismo.
	4. Características de la específica aplicación.

**Ley de Amdahi’s:** Establece que la capacidad de un incremento en velocidad está definido por la fracción de código P que puede ser paralelizado. Si no existe una proporción de paralelismo, P = 0; Speedup = 1. Si todo el algoritmo es paralelizable, P = 1; Speedup = Infinito (teóricamente). 

**Supercómputo/HPC:** Utilizar las computadoras más rápidas y grandes del mundo para resolver problemas grandes.

**CPU (Central Processing Unit):** Es una ejecución singular de un componente en una computadora.

**Socket:** Es un procesador conformado por núcleos diferentes que son capaces de correr una unidad de ejecución cada uno.

**Núcleo:** Tiene la capacidad de correr una unidad de ejecución. Es un elemento del Socket.

**Tarea:** Una sección lógica de trabajo computacional. Una tarea es comúnmente un conjunto de instrucciones de un programa  que pueden ser ejecutados por procesadores múltiples.

**Pipeline:** Dividir uan tarea en varios pasos ejecutados por unidades de procesamiento diferentes. Es muy parecido a una línea de producción; es un tipo de cómputo paralelo.

**Memoria compartida:** Arquitectura de una computadora en donde todos los procesadores tienen acceso directo a una memoria física común. En el sentido de programación, describe un modelo en donde las tareas paralelas tienen la misma imagen de memoria, pueden referenciar y acceder directamente la misma memoria lógica sin importar en donde esté localizada la memoria física.

**Multi-procesador simétrico:** Arquitectura de hardware donde procesadores múltiples comparten un mismo espacio de referencia y tienen acceso a todos los recursos; computación de memoria compartida.

**Memoria distribuida:** En hardware, se refiere a la red basada en accesos de memoria para memoria física que no es común. En programación, son tareas que pueden ver lógicamente la memoria de una computadora y deben comunicarse para acceder a memoria en otras computadoras en donde las tareas se están ejecutando.

**Comunicaciones:** Tareas paralelas que necesitan intercambiar datos. Existen distintas maneras en las que puede ser ejecutada. Una es compartir bus de memoria compartida en una red; sin embargo, el evento actual de intercambio de datos es comúnmente definido como comunicación sin importar el método empleado.

**Bibliografía**

Kung, H. T. "Synchronized and asynchronous parallel algorithms for multiprocessors." (1976).
Grama, Ananth, ed. Introduction to parallel computing. Pearson Education, 2003.
