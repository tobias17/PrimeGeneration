#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 24

struct ThreadData {
    int start;
    int stop;
    int result;
    int* primes;
};

extern int* gen_prime_numbers(int max, int* count, bool go_one_past);
extern int count_prime_numbers(int start, int stop, int* primes);

void* thread_func(void* vparg) {
    struct ThreadData* td = (struct ThreadData*) vparg;
    (*td).result = count_prime_numbers((*td).start, (*td).stop, (*td).primes);
}

int run(int max) {
    int gen_count;
    int gen_amnt = (int) sqrt(max);
    int* primes = gen_prime_numbers(gen_amnt, &gen_count, true);

    pthread_t threads[NUM_THREADS];
    struct ThreadData thread_data[NUM_THREADS];

    int start = primes[gen_count-1];
    int amount_per = (max - start) / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].start = start + amount_per * i + 1;
        if (thread_data[i].start % 2 == 0) thread_data[i].start++;
        thread_data[i].stop = (i < NUM_THREADS - 1) ? start + amount_per * (i+1) : max;
        thread_data[i].primes = primes;
        pthread_create(&threads[i], NULL, thread_func, (void*)&thread_data[i]);
    }

    int count = 0;
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
        count += thread_data[i].result;
    }

    return count + gen_count;
}
