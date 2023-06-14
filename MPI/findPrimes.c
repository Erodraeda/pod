#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define UPPER_LIMIT 100000
#define LOWER_LIMIT 1

clock_t start, end;
double cpu_time_used;

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

int findPrimesInRange(int lowerRange, int upperRange) {

    int i, numberOfPrimes = 0;
    
    for (i = lowerRange; i <= upperRange; i++) {
        if (isPrime(i)) {
            numberOfPrimes++;
        }
    }

    return numberOfPrimes;

}

void main() {

    start = clock();

    int numberOfPrimes;

    numberOfPrimes = findPrimesInRange(LOWER_LIMIT, UPPER_LIMIT);

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%lf to find %d primes between %d and %d\n\n", cpu_time_used, numberOfPrimes, LOWER_LIMIT, UPPER_LIMIT);

}



