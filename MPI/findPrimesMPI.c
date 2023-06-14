#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#define UPPER_LIMIT 100000
#define LOWER_LIMIT 1

int process_count, my_rank, mallocCounter = 0;

int isPrime(int number) {
    int count, d;

    count = (int)(sqrt((double)number)+0.0001);

    for (d = 2; d <= count; d++) {
        if (number % d == 0) {
            return 0;
        }
    }
    return 1;
}

void findPrimes(int argc, char **argv) {

    double share = (double)UPPER_LIMIT / process_count;

    int min, max;

    min = (my_rank == 0) ? LOWER_LIMIT : (int)(my_rank * share) + 1;
    max = (my_rank == process_count - 1)? UPPER_LIMIT : (int)((my_rank + 1) * share);

    int count = 0, i;

    if (my_rank != 0) {

        for (i = min; i <= max; i++) {
            if (isPrime(i)) {
                count++;
            }
        }

        int data_to_send[3];

        data_to_send[0] = count;
        data_to_send[1] = min;
        data_to_send[2] = max;

        MPI_Send(data_to_send, 3, MPI_INT, 0, 0, MPI_COMM_WORLD);

   } else {

        double start = MPI_Wtime();

        for (i = min; i <= max; i++) {
            if (isPrime(i)) {
                count++;
            }
        }

        printf("Process 0 reports %d primes between %d and %d.\n", count, min, max);

        int ct;

        for (ct = 1; ct < process_count; ct++) {

            int data_received[3];
            MPI_Status status;
            MPI_Recv(data_received, 3, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            count += data_received[0];

            printf("Process %d reports %d primes between %d and %d.\n", status.MPI_SOURCE, data_received[0], data_received[1], data_received[2]);

        }

        double elapsedTime = MPI_Wtime() - start;

        printf("\n%lf to find %d between %d and %d\n\n", elapsedTime, count, LOWER_LIMIT, UPPER_LIMIT);

        // Salvando num arquivo pra ficar mais fácil de somar na planilha sem ter que copiar

        FILE *file;

        if ((file = fopen("speeds.txt", "a")) == NULL) {
            printf("failed to open file");
        } else {
            fprintf(file, "%lf\n", elapsedTime);
        }

    }
}

void main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    
    findPrimes(argc, argv);
    
    MPI_Finalize();

}



