#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int counter(int maxNumber, int selectedMultiple) {

    int i = 0;

    int total = 0;

    for (i = 0; i < maxNumber; i++) {
        if (i % selectedMultiple == 0) {
            printf(" %d\n", i);
            total++;
        }
    }

    return total;

}

void main() {

    int threeMult = counter(10000000, 3);

    int fiveMult = counter(10000000, 5);

    int sevenMult = counter(10000000, 7);

    int nineMult = counter(10000000, 9);

    printf(" Multiplos de 3: %d\n", threeMult);

    printf(" Multiplos de 5: %d\n", fiveMult);

    printf(" Multiplos de 7: %d\n", sevenMult);

    printf(" Multiplos de 9: %d\n", nineMult);


}