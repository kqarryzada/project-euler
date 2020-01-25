// This file contains utility functions that are related to numberic computations or properties of
// numbers.
//
#ifndef NUMBERS_H
#define NUMBERS_H

#include <inttypes.h>
#include <stdbool.h>

#endif

// Converts a single character from a string representation to an integer. Returns -1 if an invalid
// input is provided.
// 
int32_t ascii_to_number(char num_char);

// Obtains the largest prime factor as long as 'number' is not prime itself, or less than 2.
// Otherwise, 0 is returned.
// 
uint64_t get_largest_prime_factor(uint64_t number);

// Returns the total number of divisors of n, including 1 and n. For example, 4 has three divisors,
// which are 1, 2, and 4.
// 
uint32_t get_num_divisors(uint64_t n);

bool is_prime(uint64_t n);

bool is_number(char* ptr);

// Determines whether the value is a palindrome in base 10.
// 
bool is_palindrome(uint32_t num);

// Checks that there is a singular numeric input and returns it as a uint64_t. If the input provided
// to the function is invalid, a message will be printed to STDERR and 0 will be returned.
// 
uint64_t parse_numeric_input(int32_t argc, char** argv);
