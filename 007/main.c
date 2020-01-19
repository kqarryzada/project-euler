// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
// What is the 10,001st prime number?

#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "../lib/numbers.h"

#define N 10001


int32_t main(void) {
    // "It's time to c-c-c-c-c-c-count!"
    int32_t count = 0;
    uint64_t i;
    for (i = 2; count != N; i++) {
        if (i == 0) {
            // overflow happened, just terminate
            fprintf(stderr, "Could not find the Nth prime number (for N = %d), since it is larger than %lu.\n",
                    N, ULONG_MAX);
            return -1;
        }

        if (is_prime(i)) {
            count++;
        }
    }
    i--;    // i will always be incremented one extra time

    printf("For N = %d, the Nth prime is %lu.\n", N, i);
    return 0;
}
