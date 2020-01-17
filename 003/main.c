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

#define DEFAULT_INPUT 600851475143
#define DEBUG 1


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

        sscanf(argv[1], "%ld", &value);
        if (value == 0) {
            // 0 is not a prime number, and doesn't make sense as an input
            fprintf(stderr, "0 is not a valid input.\n");
            return 0;
        }
    }
    else {
        fprintf(stderr, "Invalid number of parameters detected.\n");
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 0;
    }

    return value;
}


int main(int argc, char** argv) {
    // 'value' is the number whose largest prime factor we are trying to find.
    uint64_t value = parse_input(argc, argv);
    if (value == 0) {
        // Error message has already been printed; just terminate
        return -1;
    }

#ifdef DEBUG
    printf("Value is: %ld.\n", value);
#endif

    uint64_t N = value;
    // Per Fermat's factorization algorithm, N should be odd
    while ((N % 2) == 0) {
        N = N / 2;
    }

    // Calculate "a" and "b" based on Fermat's factorization algorithm
    uint64_t a = (uint64_t) sqrt((double) N);
    a++;

    while (a != N) {
        double b_squared = a * a - N;
        double b_float = sqrt(b_squared);
        uint64_t b = (uint64_t) b_float;
        if (b_float == b) {
            // If integer and float values are equal, then b_squared is a perfect square. If that's
            // true, then we have found an "a" and a "b" such that:
            // N^2 = a^2 - b^2 ==> N^2 = (a + b)(a - b)
            //
            printf("The largest prime factor of %ld is %ld.\n", value, a + b);
            return 0;
        }

        // b_squared was not a perfect square this iteration; increment a and try again.
        a++;
    }

    // If we escape the loop, it means N must be prime. If N == value, then "value" was prime to
    // begin with.
    if (value == N) {
        printf("There exists no largest prime factor for %ld, since it is a prime number.\n", value);
    }
    else {
        printf("The largest prime factor of %ld is %ld.\n", value, N);
    }
    return 0;
}
