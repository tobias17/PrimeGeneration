#include <stdio.h>
#include <time.h>

#define PRIMES_MAX   (10 * 1000 * 1000)

extern int run(int max);

int main() {
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int count = run(PRIMES_MAX);

    printf("Found %i primes below %i\n", count, PRIMES_MAX);

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Calculation took %.3f ms\n", elapsed*1000);

    return 0;
}