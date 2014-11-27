#include <stdio.h>
#include <mpi.h>

main(int argc, char** argv) {
    int         R;   /* My process rank           */
    int         P;   /* The number of processes   */
    int         ping = 1;  /* server process of ping-pong */
    int         pong = 2;  /* defender process of ping-pong */
    int         tag = 0;
    int         n = 0;   /* number of ping-pong's back and forth */
    const int size = 250000; /* length of message */
    int         k[size];   /* message content */
    int         i;
    float       x = 0;  /* for the multiply-add loop */
    char       *s;
    MPI_Status  status;
    MPI_Comm    World = MPI_COMM_WORLD;
    double      start_time, elapsed_time; /* for time measurement */

    if (atoi(argv[1]) < 6) 
    {	printf("Usage: %s n [where n is number of ping-pong steps ]\n", argv[0]);
	return 0;
    }

    /* Let the system do what it needs to start up MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(World, &P); // number of procs
    if (P < 3) { printf("this requires 3 processes\n"); return 0; }
    MPI_Comm_rank(MPI_COMM_WORLD, &R); // my rank in [0..P).
    if (R == 0) printf( "%d %d %s\n", n, argc, argv[0]);

    //n = atoi(argv[1]);  // for some reason, trouble finding atoi().
    for (s = argv[1]; *s > 0; ++s) n = 10*n + (*s - '0');
    printf("n is %d\n ", n);
    
    // measure an arithmetic time
    MPI_Barrier(World);
    if (R == ping)
    {   start_time = MPI_Wtime();
        for(i = 0; i < size; ++i) x += i*i;
	elapsed_time = MPI_Wtime() - start_time;
        printf("%d multiply-adds in %g seconds, ", n, elapsed_time);
	printf(" for an average time of %g\n", elapsed_time/size);
    }

    // measure per send communication time
    MPI_Barrier(World);
    if (R == ping) /* Note:  it is not always valid that process one can output */
    {   start_time = MPI_Wtime();
	for (i = 0; i < n; ++i)
	{   k[0] = i;
	    MPI_Send(k, 1, MPI_INT, pong, tag, World);
	    MPI_Recv(k, 1, MPI_INT, pong, tag, World, &status);
	    if (k[0] != i+1) printf("invalid pong received\n");
	}
	elapsed_time = MPI_Wtime() - start_time;
        printf("%d ping-pongs in %g seconds, ", n, elapsed_time);
	printf(" for an average message time of %g\n", elapsed_time/(2*n));
    }

    if (R == pong) 
	for (i = 0; i < n; ++i)
	{   MPI_Recv(k, 1, MPI_INT, ping, tag, World, &status);
	    if (k[0] != i) printf("invalid ping received\n");
	    k[0]  += 1;
	    MPI_Send(k, 1, MPI_INT, ping, tag, World);
	}

    // measure per byte moved communication time
    MPI_Barrier(World);
    if (R == ping) /* Note:  it is not always valid that process one can output */
    {   start_time = MPI_Wtime();
	for (i = 0; i < n; ++i)
	{   k[0] = i;
	    MPI_Send(k, size, MPI_INT, pong, tag, World);
	    MPI_Recv(k, size, MPI_INT, pong, tag, World, &status);
	    if (k[0] != i+1) printf("invalid pong received\n");
	}
	elapsed_time = MPI_Wtime() - start_time;
        printf("%d ping-pongs in %g seconds, ", n, elapsed_time);
	printf(" for an average message time of %g\n", elapsed_time/(2*n*size));
    }

    if (R == pong) 
	for (i = 0; i < n; ++i)
	{   MPI_Recv(k, size, MPI_INT, ping, tag, World, &status);
	    if (k[0] != i) printf("invalid ping received\n");
	    k[0]  += 1;
	    MPI_Send(k, size, MPI_INT, ping, tag, World);
	}

    /* Shut down MPI */
    MPI_Finalize();
} /*  main  */

