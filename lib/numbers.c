#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "numbers.h"


// Converts single-digit number from string value to integer. Returns -1 if an improper value is
// provided.
int32_t ascii_to_number(char num_char) {
    int32_t num = (int32_t) num_char - 0x30;
    if (num > 9 || num < 0) {
        return -1;
    }

    return num;
}


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
    uint64_t sqrt_n = (uint64_t) sqrt((double) n);
    sqrt_n++;

    // Loop over all odd numbers up to ceil(sqrt(n))
    for (int32_t i = 3; i < sqrt_n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}


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


bool is_palindrome(uint32_t num) {
    // Convert 'num' to string
    char num_string[sizeof(char) * 10];
    sprintf(num_string, "%u", num);

    // 'n' is the index of the last element of the string
    int32_t n = strlen(num_string) - 1;
    for (int32_t i = 0; i <= n / 2; i++) {
        if (num_string[i] != num_string[n - i]) {
            return false;
            break;
        }
    }

    return true;
}


// This returns the input value to the program as a uint64_t. If the input provided to the program
// is invalid, a message will be printed to STDERR and this method will return 0.
uint64_t parse_numeric_input(int32_t argc, char** argv) {
    uint64_t value;
    if (argc == 2) {
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
