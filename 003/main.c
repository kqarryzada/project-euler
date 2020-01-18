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

#define DEFAULT_INPUT 600851475143


bool is_number(char* ptr) {
    while (*ptr != 0) {
        if (!isdigit(*ptr)) {
            return false;
        }
        ptr++;
    }

    // Went through whole string, and all were digits
    return true;
}


// This returns the input value to the program as a uint64_t. If the input provided to the program
// is invalid, a message will be printed to STDERR and this method will return 0.
uint64_t parse_input(int argc, char** argv) {
    uint64_t value;
    if (argc == 1) {
        value = DEFAULT_INPUT;
    }
    else if (argc == 2) {
        char* input = argv[1];
        if (!is_number(input)) {
            fprintf(stderr, "'%s' is not a valid number.\n", input);
            return 0;
        }

        sscanf(argv[1], "%lu", &value);
        if (value == 0) {
            // 0 is not a prime number, and doesn't make sense as an input
            fprintf(stderr, "0 is not a valid input.\n");
            return 0;
        }
        if (value == ULONG_MAX) {
            // Likely, a number too large was entered. However, first check for the case where the
            // exact value of ULONG_MAX was entered, since that is a legitimate use case. If not,
            // then display an error.
            char* ulong_max_str = malloc(sizeof (char) * 50);
            sprintf(ulong_max_str, "%lu", ULONG_MAX);
            if (strcmp(input, ulong_max_str) != 0) {
                fprintf(stderr, "%s is too large. The largest acceptable value is %lu.\n", input, ULONG_MAX);
                value = 0;
            }
            free(ulong_max_str);
            return value;
        }
    }
    else {
        fprintf(stderr, "Invalid number of parameters detected.\n");
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 0;
    }

    return value;
}


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

int main(int argc, char** argv) {
    // 'value' is the number whose largest prime factor we are trying to find.
    uint64_t value = parse_input(argc, argv);
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
