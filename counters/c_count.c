#include <stdbool.h>
#include <math.h>

int count_prime_numbers(int start, int stop, int* primes) {
    int count = 0;

    int root = (int) sqrt(start);
    int square = root * root;

    for (int n = start; n <= stop; n += 2) {

        // see if we need to update our root
        if (square < n) {
            root++;
            square = root * root;
        }

        // loop through all primes as divisor
        for (int i = 0; true; ++i) {
            if (primes[i] > root) {
                // past root, found prime
                count++;
                break;
            }
            if (n % primes[i] == 0) {
                // not prime
                break;
            }
        }
    }

    return count;
}