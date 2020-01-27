// The following iterative sequence is defined for the set of positive integers:
// 
// n → n/2 (n is even)
// n → 3n + 1 (n is odd)
// 
// Using the rule above and starting with 13, we generate the following sequence:
// 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
// It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although
// it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at
// 1. Which starting number, under one million, produces the longest chain? 
// NOTE: Once the chain starts the terms are allowed to go above one million.

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

// No term in the chain may go above this value
#define CHAIN_THRESHOLD 1000000

#define INVALID -1


int32_t* chain_list;


// If n is a starting term, this function returns how many terms are in the sequence.
int32_t find_chain_value(int64_t n) {
    if (n < 1) {
        return INVALID;
    }
    if (n == 1) {
        // There is one term in a sequence with a starting term n == 1.
        return 1;
    }
    if (n < CHAIN_THRESHOLD && chain_list[n] != 0) {
        // If non-zero, it has already been defined. Return that value.
        return chain_list[n];
    }

    // Find the "chain value" (e.g., distance from 1) of the next term
    int64_t next_term = (n % 2 == 0) ? n / 2 : 3*n + 1;
    int32_t chain_value = find_chain_value(next_term);

    // Only increment the value returned was valid.
    if (chain_value != INVALID) {
        chain_value++;
    }

    // Set the value in 'chain_list' for future use as long as it falls within the valid range
    if (n < CHAIN_THRESHOLD) {
        chain_list[n] = chain_value;
    }
    return chain_value;
}


int32_t main(void) {
    chain_list = calloc(CHAIN_THRESHOLD, sizeof(int32_t));
    chain_list[0] = INVALID;    // 0 is not considered for this problem
    chain_list[1] = 1;
    int32_t longest_value = 0;
    int32_t longest_key = 0;

    for (int64_t i = 1; i < CHAIN_THRESHOLD; i++) {
        int32_t check = find_chain_value(i);
        if (check > longest_value) {
            longest_value = check;
            longest_key = i;
        }
    }

    printf("For a threshold of %d, the longest sequence defined by the Collatz Problem"
           " is %d with a chain length of %d.\n\n", CHAIN_THRESHOLD, longest_key, longest_value);
    free(chain_list);
    return 0;
}
