#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "numbers.h"

#define DEFAULT_ARR_SIZE 20


// Converts single-digit number from string value to integer. Returns -1 if an improper value is
// provided.
int32_t ascii_to_number(char num_char) {
    int32_t num = (int32_t) num_char - 0x30;
    if (num > 9 || num < 0) {
        return -1;
    }

    return num;
}


// Uses Fermat's factorization algorithm to return the largest prime factor of 'number'. If 'number'
// is prime, or if a number less than 2 is given, 0 is returned.
uint64_t get_largest_prime_factor(uint64_t number) {
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
                factor1 = get_largest_prime_factor(factor1);
            }
            if (!is_prime(factor2)) {
                factor2 = get_largest_prime_factor(factor2);
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


uint32_t get_num_divisors(uint64_t n) {
    uint64_t* factors_list = malloc(DEFAULT_ARR_SIZE * sizeof(uint64_t));
    uint32_t len = 0;
    uint32_t max_len = DEFAULT_ARR_SIZE;

    // First, construct the list of prime factors:
    while (n > 1) {
        int64_t factor = get_largest_prime_factor(n);
        if (factor == 0) {
            // n is prime. Set "factor" to be n itself, so that it may be added to the list.
            factor = n;
        }
        factors_list[len] = factor;
        n /= factor;

        len++;
        if (len >= max_len) {
            max_len *= 2;
            factors_list = realloc(factors_list, max_len * sizeof(uint64_t));
        }
    }

    // When all prime factors have been found, we need to re-arrange them in the form:
    // number = a^x * b^y * c^z + ...
    //
    // so that we may find all possible divisors. This can be done by using the values of the
    // powers to calculate:
    // num_divisors = (x + 1)(y + 1)(z + 1)...
    //
    // This product calculates all possible factors. We add 1 to each power to account for the
    // 0th power. For example, 12 = 2^2 + 3^1. The list of all possible divisors is:
    // 2^0 * 3^0 = 1
    // 2^0 * 3^1 = 3
    // 2^1 * 3^0 = 2
    // 2^1 * 3^1 = 6
    // 2^2 * 3^0 = 4
    // 2^2 * 3^1 = 12
    // There are six divisors, or (2 + 1)(1 + 1).

    uint32_t powers[len];

    // Keeps track of the number of unique instances found for each factor
    uint32_t uniq = factors_list[0];

    int32_t num_powers = 0;
    for (int32_t j = 0; j < len; num_powers++) {
        // counts the number of times we find a value repeated in 'factors_list'
        int32_t count = 0;
        while (j < len && factors_list[j] == uniq) {
            j++;
            count++;
        }

        // Add 1 to account for the 0th power
        powers[num_powers] = count + 1;
        if (j < len) {
            uniq = factors_list[j];
        }
    }
    free(factors_list);

    uint32_t product = 1;
    for (int32_t i = 0; i < num_powers; i++) {
        product *= powers[i];
    }

    return product;
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
