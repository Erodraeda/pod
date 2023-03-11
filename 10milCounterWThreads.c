#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

FILE *file;

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
};

void *counter(void *arguments);
void getCurrentFile(int selectedMultiple);

void main() {

    struct args_struct arguments;

    struct args_struct threeArguments = {maxvalue, 3, "files/threadedThreeFile.txt"};
    struct args_struct fiveArguments = {maxvalue, 5, "files/threadedFiveFile.txt"};
    struct args_struct sevenArguments = {maxvalue, 7, "files/threadedSevenFile.txt"};
    struct args_struct nineArguments = {maxvalue, 9, "files/threadedNineFile.txt"};

    pthread_t thread1, thread2, thread3, thread4;

    pthread_create(&thread1, NULL, counter, (void *)&threeArguments);
    pthread_join(thread1, NULL);
    pthread_create(&thread2, NULL, counter, (void *)&fiveArguments);
    pthread_join(thread2, NULL);
    pthread_create(&thread3, NULL, counter, (void *)&sevenArguments);
    pthread_join(thread3, NULL);
    pthread_create(&thread4, NULL, counter, (void *)&nineArguments);
    pthread_join(thread4, NULL);

    system("pause");

}

void *counter(void *arguments) {

    int i = 0;

    struct args_struct *args = arguments;

    getCurrentFile(args -> selectedMultiple);

    printf("  %d\n", args -> selectedMultiple);

    int total = 0;
    if((file = fopen(args -> fileName, "w+")) == NULL) {
        printf("Erro ao abrir arquivo");
    }
    else {
        printf("arquivo aberto: %s\n", args -> fileName);
    for (i = 1; i <= args -> maxvalue; i++) {
        if (i % args -> selectedMultiple == 0) {
            total++;
            fprintf(file, "%d\n", i);
        }
    }
    fclose(file);
    }

    printf(" Multiplos de %d: %d\n", args -> selectedMultiple, total);

    pthread_exit(NULL);

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