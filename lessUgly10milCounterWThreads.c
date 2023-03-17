#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
// #include <unistd.h>

// Create file pointers
FILE *file3;
FILE *file5;
FILE *file7;
FILE *file9;

// Max value for iteration
int maxvalue = 10000000;

// Thread arguments struct
struct args_struct {
    int selectedMultiple;
    char fileName[30];
    FILE *file;
};

// Pre declaration of function
void *counter(void *arguments);


// Main function
void main() {

    // Checks if destination folder exists
    struct stat st = {0};

    if (stat("./files", &st) == -1) {
        mkdir("./files", 0700);
    }

    // Starts structs for arguments for each function
    struct args_struct arguments;

    struct args_struct threeArguments = {3, "files/threadedThreeFile.txt", file3};
    struct args_struct fiveArguments = {5, "files/threadedFiveFile.txt", file5};
    struct args_struct sevenArguments = {7, "files/threadedSevenFile.txt", file7};
    struct args_struct nineArguments = {9, "files/threadedNineFile.txt", file9};

    // Thread declaration
    pthread_t thread1, thread2, thread3, thread4;

    // Creates threads
    pthread_create(&thread1, NULL, counter, (void *)&threeArguments);
    pthread_create(&thread2, NULL, counter, (void *)&fiveArguments);
    pthread_create(&thread3, NULL, counter, (void *)&sevenArguments);
    pthread_create(&thread4, NULL, counter, (void *)&nineArguments);

    // Waits for threads to finish their duties
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    return 0;

}

// Counter function
void *counter(void *arguments) {

    // Starts struct for arguments
    struct args_struct *args = arguments;

    printf(" %d\n", args -> selectedMultiple);

    int total = 0;

    // Checks if file can be successfully opened
    if((args -> file = fopen(args -> fileName, "w+")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {
        // Iterates up to the maxvalue declared
        printf("arquivo aberto: %s\n", args -> fileName);
        for (int i = 1; i <= maxvalue; i++) {
            if (i % args -> selectedMultiple == 0) {
                total++;
                // Saves data to the file
                fprintf(args -> file, "%d\n", i);
            }
        }
        // Closes file
        fclose(args -> file);
    }

    printf(" Multiplos de %d: %d\n", args -> selectedMultiple, total);

    return 0;

}