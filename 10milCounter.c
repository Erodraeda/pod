#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *file3;
FILE *file5;
FILE *file7;
FILE *file9;

char threeFileName[30] = "files/threeFile.txt";
char fiveFileName[30] = "files/fiveFile.txt";
char sevenFileName[30] = "files/sevenFile.txt";
char nineFileName[30] = "files/nineFile.txt";
char fileName[30];

int maxvalue = 10000000;

struct args_struct {
    int maxvalue;
    int selectedMultiple;
    char fileName[30];
    FILE *file;
};

int *counter(void *arguments);
void getCurrentFile(int selectedMultiple);

void main() {

    struct args_struct arguments;

    struct args_struct threeArguments = {maxvalue, 3, "files/threeFile.txt", file3};
    struct args_struct fiveArguments = {maxvalue, 5, "files/fiveFile.txt", file5};
    struct args_struct sevenArguments = {maxvalue, 7, "files/sevenFile.txt", file7};
    struct args_struct nineArguments = {maxvalue, 9, "files/nineFile.txt", file9};

    int threeMult = counter(&threeArguments);

    int fiveMult = counter(&fiveArguments);

    int sevenMult = counter(&sevenArguments);

    int nineMult = counter(&nineArguments);

    printf(" Multiplos de 3: %d\n", threeMult);

    printf(" Multiplos de 5: %d\n", fiveMult);

    printf(" Multiplos de 7: %d\n", sevenMult);

    printf(" Multiplos de 9: %d\n", nineMult);

    system("pause");

}

int *counter(void *arguments) {

    struct args_struct *args = arguments;

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

    return total;

}