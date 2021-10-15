#include <stdbool.h>
#include <math.h>

extern int* gen_prime_numbers(int max, int* count, bool go_one_past);
extern int count_prime_numbers(int start, int stop, int* primes);

int run(int max) {
    int gen_count;
    int gen_amnt = (int) sqrt(max);
    int* primes = gen_prime_numbers(gen_amnt, &gen_count, true);

    int other_count = count_prime_numbers(primes[gen_count-1] + 2, max, primes);
    int total_count = gen_count + other_count;
}