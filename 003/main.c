// The prime factors of 13195 are 5, 7, 13 and 29.
// What is the largest prime factor of the number 600851475143?

#include <ctype.h>
#include <limits.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/numbers.h"

#define DEFAULT_INPUT 600851475143


// Uses Fermat's factorization algorithm to return the largest prime factor of 'number'. If 'number'
// is prime, or if a number less than 2 is given, 0 is returned.
uint64_t find_largest_prime_factor(uint64_t number) {
    // By definition, 0 and 1 are not prime. 2 is an edge case since it is prime, but even.
    if (number < 3) {
        return 0;
    }

    // Per Fermat's factorization algorithm, N should be odd
    uint64_t N = number;
    while ((N % 2) == 0) {
        N = N / 2;
    }
    // After halving N repeatedly, if N == 1, then we know 'number' must be a power of 2.
    if (N == 1) {
        return 2;
    }


    // Set 'a' as the algorithm requires. a = ceil(sqrt(N))
    double a_float = sqrt((double) N);
    uint64_t a = (uint64_t) a_float;
    // if a == a_float, then a is already equivalent to ceil(sqrt(N)). Otherwise, increment it.
    if (a != a_float) {
        a++;
    }

    while (a != N) {
        double b_squared = a * a - N;
        double b_float = sqrt(b_squared);
        uint64_t b = (uint64_t) b_float;
        if (b_float == b) {
            // If integer and float values are equal, then b_squared is a perfect square. If that's
            // true, then we have found an "a" and a "b" such that:
            // N^2 = a^2 - b^2 ==> N^2 = (a + b)(a - b)
            uint64_t factor1 = a + b;
            uint64_t factor2 = a - b;

            // If either factor is equivalent to N, then N is prime.
            if (factor1 == N || factor2 == N) {
                break;
            }

            // Recursively obtain the largest prime factors of each factor, if they are not already
            // prime.
            if (!is_prime(factor1)) {
                factor1 = find_largest_prime_factor(factor1);
            }
            if (!is_prime(factor2)) {
                factor2 = find_largest_prime_factor(factor2);
            }
            
            return (factor1 > factor2) ? factor1 : factor2;
        }

        // b_squared was not a perfect square this iteration; increment 'a' and try again.
        a++;
    }

    // If we escape the loop, it means N must be prime. If N == number, then the value given to this
    // function was prime to begin with.
    return (N == number) ? 0 : N;
}

int32_t main(int32_t argc, char** argv) {
    // 'value' is the number whose largest prime factor we are trying to find.
    uint64_t value;

    if (argc == 1) {
        // Use default value
        value = DEFAULT_INPUT;
    }
    else {
        value = (uint64_t) parse_numeric_input(argc, argv);
    }
    if (value == 0) {
        // Error message has already been printed in parse_input()— just terminate
        return -1;
    }
    if (value == 1) {
        fprintf(stderr, "The value requested was %lu, which is not a valid parameter.\n", value);
        return -1;
    }

    uint64_t factor = find_largest_prime_factor(value);
    if (factor == 0) {
        printf("%lu is a prime number, so it does not have a prime factor other than itself.\n", value);
    }
    else {
        printf("The largest prime factor of %lu is %lu.\n", value, factor);
    }
}
