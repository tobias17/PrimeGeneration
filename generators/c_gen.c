#include <stdlib.h>
#include <stdbool.h>

#define SIZE_DIVISOR 50

int* grow_array(int* old_arr, size_t old_size, size_t new_size) {
    int* new_arr = malloc(new_size * sizeof(int));

    for (int i = 0; i < old_size; ++i) {
        new_arr[i] = old_arr[i];
    }

    free(old_arr);
    return new_arr;
}

int* gen_prime_numbers(int max, int* count, bool go_one_past) {
    size_t amount_per = max / SIZE_DIVISOR;
    size_t curr_size = amount_per;

    int* arr = malloc(curr_size * sizeof(int));
    arr[0] = 2;
    arr[1] = 3;
    int index_on = 2;

    int root = 3;
    int square = root * root;
    bool on_last = false;
    bool finished = false;

    // check all odd numbers for prime status
    for (int n = 5; !finished; n += 2) {

        // see if we need to update our root
        if (square < n) {
            root++;
            square = root * root;
        }

        // loop through all primes as divisor
        for (int i = 0; true; ++i) {
            if (arr[i] > root || i >= index_on) {
                // past root, found prime
                arr[index_on] = n;
                index_on++;

                // realloc if past size
                if (index_on >= curr_size) {
                    arr = grow_array(arr, curr_size, curr_size + amount_per);
                    curr_size += amount_per;
                }

                if (n >= max) {
                    if (!go_one_past || on_last) {
                        // we do not need extra or already got extra
                        finished = true;
                    }
                    on_last = true;
                }
                break;
            }
            if (n % arr[i] == 0) {
                // not prime
                break;
            }
        }

        if (!go_one_past && n >= max) {
            break;
        }
    }

    *count = index_on;
    return arr;
}