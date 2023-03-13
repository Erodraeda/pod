#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

FILE *file3;
FILE *file5;
FILE *file7;
FILE *file9;

char threeFileName[30] = "files/threadedThreeFile.txt";
char fiveFileName[30] = "files/threadedFiveFile.txt";
char sevenFileName[30] = "files/threadedSevenFile.txt";
char nineFileName[30] = "files/threadedNineFile.txt";

char fileName[30];

int maxvalue = 10000000;

struct args_struct {
    int maxvalue;
    int selectedMultiple;
    char fileName[30];
    FILE *file;
};

void *counter(void *arguments);
void getCurrentFile(int selectedMultiple);

void main() {

    struct args_struct arguments;

    struct args_struct threeArguments = {maxvalue, 3, "files/threadedThreeFile.txt", file3};
    struct args_struct fiveArguments = {maxvalue, 5, "files/threadedFiveFile.txt", file5};
    struct args_struct sevenArguments = {maxvalue, 7, "files/threadedSevenFile.txt", file7};
    struct args_struct nineArguments = {maxvalue, 9, "files/threadedNineFile.txt", file9};

    pthread_t thread1, thread2, thread3, thread4;

    pthread_create(&thread1, NULL, counter, (void *)&threeArguments);
    pthread_create(&thread2, NULL, counter, (void *)&fiveArguments);
    pthread_create(&thread3, NULL, counter, (void *)&sevenArguments);
    pthread_create(&thread4, NULL, counter, (void *)&nineArguments);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    return 0;

}

void *counter(void *arguments) {

    struct args_struct *args = arguments;

    getCurrentFile(args -> selectedMultiple);

    printf(" %d\n", args -> selectedMultiple);

    int total = 0;

    if((args -> file = fopen(args -> fileName, "w+")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {
        printf("arquivo aberto: %s\n", args -> fileName);
        for (int i = 1; i <= args -> maxvalue; i++) {
            if (i % args -> selectedMultiple == 0) {
                total++;
                fprintf(args -> file, "%d\n", i);
            }
        }
        fclose(args -> file);
    }

    printf(" Multiplos de %d: %d\n", args -> selectedMultiple, total);

    return 0;

}

void getCurrentFile(int selectedMultiple) {

    switch(selectedMultiple) {

        case 3:
            strcpy(fileName, threeFileName);
            break;
        case 5:
            strcpy(fileName, fiveFileName);
            break;
        case 7:
            strcpy(fileName, sevenFileName);
            break;
        case 9:
            strcpy(fileName, nineFileName);
            break;
    }

}