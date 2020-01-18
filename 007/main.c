// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
// What is the 10,001st prime number?

#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define N 10001

bool is_prime(uint64_t n) {
    // 2 is an edge case, since it is the only even prime number
    if (n == 2) {
        return true;
    }
    // - Primes are defined only for numbers > 1
    // - Even numbers (except n == 2) are not prime
    if (n < 2 || n % 2 == 0) {
        return false;
    }

    // To check if a number is prime, we only have to check up to the square root of that number.
    // Increment this value to avoid edge case where sqrt_n == 3 does not enter the main loop
    uint64_t sqrt_n = (uint64_t) sqrt((double) n);
    sqrt_n++;

    // Loop over all odd numbers up to floor(sqrt(n))
    for (int i = 3; i < sqrt_n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}


int main(void) {
    // "It's time to c-c-c-c-c-c-count!"
    int count = 0;
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
