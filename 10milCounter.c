#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int foundNumbers[2500000] = {};
int top = 0;

void push()
{
    if(top>=n-1)
    {
        printf("\n\tSTACK is over flow");
        
    }
    else
    {
        printf(" Enter a value to be pushed:");
        scanf("%d",&x);
        top++;
        foundNumbers[top]=x;
    }
}

int counter(int maxNumber, int selectedMultiple) {

    int i = 0;

    for (i = 0; i < maxNumber; i++) {
        if (i % selectedMultiple == 0) {
            printf("%d", i);
            push();
        }
    }

}

void main() {

    counter(10000000, 3);
    
    int i = 0;

    for (i = 0; i < 2500000; i++) {
        printf("%d", foundNumbers[i]);
    }

    top = 0;

}