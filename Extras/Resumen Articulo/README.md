# Resumen del artículo: Summary of Article: Energy profile of rollback-recovery strategies in high performance computing

* ¿De que trata el artículo?
		* There 2 problems to analize when implementing HPC:
			- Fault tolerance
    	- Energy comsumption
  	* This article explains the analysis of 3 rollback-recovery techniques

* ¿Cómo utilizan el HPC en el artículo?
	* 3 techniques for rollback-recovery are:
  	-	Checkpoint/restart: The most popular strategy to provide fault tolerance in HPC is checkpoint/restart. The basic tenet of this protocol is to
     		checkpoint, or save the state of the application with certain periodicity, such that a failure will roll back all the nodes to
     		a previous state and resume the execution from that state. The principle is simple and effective for the failure frequency
     		of petascale machines. There are several libraries implementing this protocol for HPC systems
  	- Message logging: A node failure provokes the loss of the current state of the tasks running on the failed node. To reconstruct that state,
   	  	checkpoint/restart rolls back the set of all tasks to a previous consistent checkpoint and resumes execution. Rolling back
   	  	the tasks that did not fail is unnecessary, provided that the messages those tasks sent to the failed tasks can be somehow
   	  	recovered.
  	- Parallel recovery: The main idea of this strategy consists in distributing the tasks on the failed node among other nodes during restart.
   	  	That way, if the application is tightly coupled and most nodes are idle during recovery, the recovering tasks can recover
   	  	on different nodes and in parallel. A faster recovery provides a mechanism to achieve a faster execution in a faulty
   	  	environment.

* ¿Qué rendimiento/resultados son obtenidos en el artículo?
	- The reasoning minimize execution time will minimize energy consumption is invalid in the context of faulty machines. Mes-
   sage logging is a good example of that. It incurs performance overhead due to the additional function it performs (storing
   messages and determinants), but recovery is significantly more efficient in energy terms.

	- Neither message logging nor parallel recovery significantly increase power draw. These protocols may, though, increase
   energy consumption in a failure-free execution due to the performance overhead of the message logging protocol.

	- In an HPC environment, parallel recovery satisfies the requirements of both users (minimum execution time) and system 
     administrators (minimum energy consumption).

	- The analytical model predicts a substantial reduction in energy consumption by using parallel recovery. For a large-scale
   system with more than 512,000 sockets, parallel recovery will be able to reduce the total energy consumption by more
   than 37%, compared to checkpoint/restart.

* ¿Qué opinión tienes respecto al artículo?
	- This article seems to be a very importante advance in the HPC field due to the fact that help to reduce the power consumption
  	and waste of time during the excecution of HPC problems. The conclusion was they reach a reduction of 37% of reduction int he total
  	energy consumption is a huge reduction in terms of monetary cost. This article shows how the SW can helps to improve the power and
  	performance that the HW could not achieve.

* Si fueras árbitro del artículo, ¿Qué pregunta harías al autor del artículo?
	- Which are the next steps to implement these protocols and improvements in real life technology?
  - Does it apply to all kind of enviroments or it has constrains in SW, OS or micro process architecture?
