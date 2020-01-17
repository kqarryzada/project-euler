// The prime factors of 13195 are 5, 7, 13 and 29.
// What is the largest prime factor of the number 600851475143?
//
// This program uses Fermat's factorization method to answer the question.

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// #define DEFAULT_INPUT 600851475143
#define DEFAULT_INPUT 60
#define DEBUG 1


bool is_prime(uint64_t n) {
    // Primes are defined only for numbers > 1
    if (n < 2) {
        return false;
    }
    // Check if number is even
    if (n % 2 == 0) {
        return false;
    }

    // To check if a number is prime, we only have to check up to the square root of that number.
    uint64_t sqrt_n = (uint64_t) sqrt((double) n);

    // Loop over all odd numbers up to floor(sqrt(n))
    for (int i = 3; i < sqrt_n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}


// Uses Fermat's factorization algorithm to return the largest prime factor of N. If N is prime, 0
// is returned.
uint64_t find_largest_prime_factor(uint64_t _N) {
    // Per Fermat's factorization algorithm, N should be odd
    uint64_t N = _N;
    while ((N % 2) == 0) {
        N = N / 2;
    }

    // a = ceil(sqrt(N))
    uint64_t a = (uint64_t) sqrt((double) N);
    a++;
#ifdef DEBUG
    printf("a starts with value: %ld\n", a);
#endif
    while (a != N) {
        double b_squared = a * a - N;
        double b_float = sqrt(b_squared);
        uint64_t b = (uint64_t) b_float;
        if (b_float == b) {
            // If integer and float values are equal, then b_squared is a perfect square. If that's
            // true, then we have found an "a" and a "b" such that:
            // N^2 = a^2 - b^2 ==> N^2 = (a + b)(a - b)
            // The algorithm states that a - b will be prime.
            #ifdef DEBUG
            printf("a is %ld and b is %ld.\n", a, b);
            #endif
            return a - b;

            // // If the factor we found is not prime, make a recursive call to find the largest prime
            // // factor of that value.
            // while (!is_prime(factor1)) {
            //     prime_factor1 = find_largest_prime_factor(factor1);
            // }

            // // 
            // return prime_factor1;
        }

        // b_squared was not a perfect square this iteration; increment a and try again.
        a++;
    }

    // If we escape the loop, it means N must be prime. If N == _N, then the value given to this
    // function was prime to begin with, so we return 0 to indicate that _N has no prime factors
    // other than itself.
    if (N == _N) {
        return 0;
    }
    else {
        return N;
    }
}

int main(void) {
    // 'value' is the number whose largest prime factor we are trying to find.
    uint64_t value = DEFAULT_INPUT;

#ifdef DEBUG
    printf("Value is: %ld.\n", value);
#endif

    uint64_t factor = find_largest_prime_factor(value);
    if (factor == 0) {
        printf("There exists no largest prime factor for %ld, since it is a prime number.\n", value);
    }
    else {
        printf("The largest prime factor of %ld is %ld.\n", value, factor);
    }
}
