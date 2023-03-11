#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *file;

char threeFileName[30] = "files/threeFile.txt";
char fiveFileName[30] = "files/fiveFile.txt";
char sevenFileName[30] = "files/sevenFile.txt";
char nineFileName[30] = "files/nineFile.txt";
char fileName[30];

int maxvalue = 10000000;

int counter(int maxNumber, int selectedMultiple);
void getCurrentFile(int selectedMultiple);

void main() {

    int threeMult = counter(maxvalue, 3);

    int fiveMult = counter(maxvalue, 5);

    int sevenMult = counter(maxvalue, 7);

    int nineMult = counter(maxvalue, 9);

    printf(" Multiplos de 3: %d\n", threeMult);

    printf(" Multiplos de 5: %d\n", fiveMult);

    printf(" Multiplos de 7: %d\n", sevenMult);

    printf(" Multiplos de 9: %d\n", nineMult);

    system("pause");

}

int counter(int maxNumber, int selectedMultiple) {

    int i = 0;

    getCurrentFile(selectedMultiple);

    int total = 0;
    if((file = fopen(fileName, "w+")) == NULL) {
        printf("Erro ao abrir arquivo");
    }
    else {
        printf("arquivo aberto: %s\n", fileName);
    for (i = 1; i <= maxNumber; i++) {
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