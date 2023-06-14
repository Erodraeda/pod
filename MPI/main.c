#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#define UPPER_LIMIT 100000

clock_t start, end;
double cpu_time_used;

int *primes;
int *q;

int process_count, my_rank, mallocCounter = 0; 
              
int get_range(int argc, char **argv) {
   if (argc < 2 || !argv[1])
      return UPPER_LIMIT;
   int range = atoi(argv[1]);
   if (range < 2*process_count)
      return UPPER_LIMIT;
   return range;
}

int is_prime(int n) {
   int count, d;
   count = (int)(sqrt((double)n)+0.0001);
   for (d = 2; d <= count; d++)
      if ( n % d == 0 )
         return 0;
   return 1;
}

void do_work(int argc, char **argv) {

   int range = get_range(argc,argv);  // Counting primes between 2 and range.
   double delta = (double)range / process_count;
   int min;  // Start of block of values for this process.
   int max;  // End of block of values for this process.
   min = (my_rank == 0)? 2 : (int)(my_rank*delta) + 1;
   max = (my_rank == process_count-1)? range : (int)((my_rank+1)*delta);

   int count = 0;  // Number of primes counted.
   
   int i;

   if ( my_rank != 0) {
          // Send count from this process to process 0.
      for (i = min; i <= max; i++)    // Count the primes.
         if (is_prime(i))
            count++;
      int data_to_send[3];
      data_to_send[0] = count;
      data_to_send[1] = min;
      data_to_send[2] = max;
      MPI_Send( data_to_send, 3, MPI_INT, 0, 0, MPI_COMM_WORLD);
   }
   else {
         // Process 0 receives the counts from all processes and adds
         // them to its own count, giving the total number of primes
         // in all blocks.
      double start = MPI_Wtime();
      for (i = min; i <= max; i++)    // Count the primes.
         if (is_prime(i))
            count++;
      printf("Process 0 reports %d primes between %d and %d.\n", count, min, max);
      int ct;
      for (ct = 1; ct < process_count; ct++) {
         int data_received[3];
         MPI_Status status;
         MPI_Recv( data_received, 3, MPI_INT, MPI_ANY_SOURCE,
                        MPI_ANY_TAG, MPI_COMM_WORLD, &status );
         count += data_received[0];
         printf("Process %d reports %d primes between %d and %d.\n", 
              status.MPI_SOURCE, data_received[0], data_received[1], data_received[2]);
      }
      printf("\nTotal number of primes between 2 and %d:  %d.\n", range, count);
      double elapsed = MPI_Wtime() - start;
      printf("\nElapsed time:  %1.3f seconds.\n", elapsed);
   }
}

void findPrimesInRange(int lowerRange, int upperRange) {

    primes = (int *)malloc(mallocCounter*sizeof(int));

    int i, count;

    while(lowerRange <= upperRange) {
        count = 0;
        i = 2;
        while(i <= lowerRange/2) {
            if(lowerRange%i == 0) {
                count++;
                break;
            }
            i++;
        }
        if(count == 0 && lowerRange != 1 ) {
            mallocCounter++;
            primes = (int *)realloc(primes, mallocCounter*sizeof(int));
            primes[mallocCounter-1] = lowerRange;
        }
        lowerRange++; 
    }

}

void MPIFindPrimes(int lowerRange, int upperRange, int numOfProcesses) {

//    MPI_INIT();

}

void printArray(int *array, int size) {

    int i;

    for (i = 0; i < size; i++) {

        printf("%d", array[i]);
        if (i != size - 1) {
            printf(", ");
        } else {
            printf("\n\n");
        }

    }

}

void main(int argc, char **argv) {

    // int ierr, num_procs, my_id;

    //   ierr = MPI_Init(&argc, &argv);

    //   /* find out MY process ID, and how many processes were started. */

    //   ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    //   ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    //   printf("Hello world! I'm process %i out of %i processes\n", 
    //      my_id, num_procs); 

    //   ierr = MPI_Finalize();

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    
    do_work(argc, argv);
    
    MPI_Finalize();

    // // start = clock();

    // printf("started");

    // int i, ierr, my_id = 0, num_procs = 1;
	// // MPI_Status status;

    // printf("mpi status");
	
	// MPI_Init(&argc, &argv);
    // printf("init");
	// ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    // printf("comm rank");
    // ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    // printf("comm size");

    // if (my_id == 0) {

    // 	// findPrimesInRange(1, 100000);

    //     printf("teste processo: %d", my_id);

	// }
	
	// ierr = MPI_Finalize();

    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

////    printArray(primes, mallocCounter);

    // printf("%lf to find %d primes\n\n", cpu_time_used, mallocCounter);

}



