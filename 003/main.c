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

    uint64_t factor = get_largest_prime_factor(value);
    if (factor == 0) {
        printf("%lu is a prime number, so it does not have a prime factor other than itself.\n", value);
    }
    else {
        printf("The largest prime factor of %lu is %lu.\n", value, factor);
    }
}
