#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char threeFileName[14] = "threeFile.txt";
char fiveFileName[14] = "fiveFile.txt";
char sevenFileName[14] = "sevenFile.txt";
char nineFileName[14] = "nineFile.txt";

char fileName[14];

int counter(int maxNumber, int selectedMultiple, FILE *file);
void getCurrentFile(int selectedMultiple);

void main() {

    FILE *threeFile;
    FILE *fiveFile;
    FILE *sevenFile;
    FILE *nineFile;

    int threeMult = counter(10000000, 3, threeFile);

    int fiveMult = counter(10000000, 5, fiveFile);

    int sevenMult = counter(10000000, 7, sevenFile);

    int nineMult = counter(10000000, 9, nineFile);

    printf(" Multiplos de 3: %d\n", threeMult);

    printf(" Multiplos de 5: %d\n", fiveMult);

    printf(" Multiplos de 7: %d\n", sevenMult);

    printf(" Multiplos de 9: %d\n", nineMult);

    system("pause");

}

int counter(int maxNumber, int selectedMultiple, FILE *file) {

    int i = 0;

    getCurrentFile(selectedMultiple);

    int total = 0;
    if((file = fopen(fileName, "w+")) == NULL) {
        printf("Erro ao abrir arquivo");
    }
    else {
        printf("arquivo aberto: %s\n", fileName);
    for (i = 0; i < maxNumber; i++) {
        if (i % selectedMultiple == 0) {
            total++;
            fprintf(file, "%d\n", i);
        }
    }
    fclose(file);
    }

    return total;

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