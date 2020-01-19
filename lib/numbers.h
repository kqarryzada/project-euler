// This file contains utility functions that are related to numberic computations or properties of
// numbers.
//


bool is_prime(uint64_t n);

bool is_number(char* ptr);

// Determines whether the value is a palindrome in base 10.
// 
bool is_palindrome(uint32_t num);

// Checks that there is a singular numeric input and returns it as a uint64_t. If the input provided
// to the function is invalid, a message will be printed to STDERR and 0 will be returned.
// 
uint64_t parse_numeric_input(int32_t argc, char** argv);
