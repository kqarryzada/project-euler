// The four adjacent digits in the 1000-digit number below that have the greatest product are 9 × 9
// × 8 × 9 = 5832. Find the thirteen adjacent digits in the 1000-digit number that have the greatest
// product. What is the value of this product?
#include <inttypes.h>
#include <stdio.h>
#include "../lib/numbers.h"

#define NUM_DIGITS 13


// The problem defines this as a 1000-digit number, but it's pretty much a list of numbers.
const char* list = "\
73167176531330624919225119674426574742355349194934\
96983520312774506326239578318016984801869478851843\
85861560789112949495459501737958331952853208805511\
12540698747158523863050715693290963295227443043557\
66896648950445244523161731856403098711121722383113\
62229893423380308135336276614282806444486645238749\
30358907296290491560440772390713810515859307960866\
70172427121883998797908792274921901699720888093776\
65727333001053367881220235421809751254540594752243\
52584907711670556013604839586446706324415722155397\
53697817977846174064955149290862569321978468622482\
83972241375657056057490261407972968652414535100474\
82166370484403199890008895243450658541227588666881\
16427171479924442928230863465674813919123162824586\
17866458359124566529476545682848912883142607690042\
24219022671055626321111109370544217506941658960408\
07198403850962455444362981230987879927244284909188\
84580156166097919133875499200524063689912560717606\
05886116467109405077541002256983155200055935729725\
71636269561882670428252483600823257530420752963450";


// Utility function to obtain the product of a sub-list of numbers, designated by starting and
// ending pointers. The pointers are inclusive, so the values for *start and *end are calculated.
uint64_t find_product(const char* start, const char* end) {
    // Increment 'end' to ensure the value of *end (before the increment) is included in the loop
    // below.
    end++;

    uint64_t product;
    for (product = 1; start != end; start++) {
        product *= ascii_to_number(*start);
    }
    return product;
}


int32_t main(void) {
    if (NUM_DIGITS < 2 || NUM_DIGITS > 13) {
        fprintf(stderr, "The NUM_DIGITS parameter was set to %d, which is invalid.\n", NUM_DIGITS);
    }

    // Initialize. Calculate the values for the first n digits before entering the loop,
    // where n == NUM_DIGITS.
    const char* start = list;
    const char* end = list + NUM_DIGITS - 1;
    uint64_t largest_product = find_product(start, end);

    // This keeps track of number of '0' characters between 'start' and 'end'. If 'largest_product'
    // is zero for the first sub-string, then there exists at least one in the sub-string. This is
    // done in an effort to avoid unneccessary multiplication.
    uint32_t num_zeroes = 0;
    if (largest_product == 0) {
        const char* start_tmp = start;
        const char* end_tmp = end;
        end_tmp++;

        while (start_tmp != end_tmp) {
            if (*start_tmp == '0') {
                num_zeroes++;
            }
            start_tmp++;
        }
    }

    // State of the first sub-string computed, increment in preparation of loop
    start++;
    end++;
    uint64_t current_product = largest_product;


    while (*end != 0) {
        int32_t prev_num = ascii_to_number(*(start - 1));
        int32_t next_num = ascii_to_number(*end);

        // First, check for zeroes
        if (next_num == 0) {
            num_zeroes++;
        }
        if (prev_num == 0) {
            num_zeroes--;
        }

        // Calculate 'current_product'
        if (num_zeroes == 0) {
            if (prev_num == 0) {
                // We just moved past a zero and have a sub-list with no zeroes, so we need to 
                // re-calculate the product, as 'current_product' was 0 in the last iteration.
                current_product = find_product(start, end);
            }
            else if (prev_num != next_num) {
                // Perform the division first to avoid overflow.
                current_product = (current_product / prev_num) * next_num;
            }
        }
        else {
            current_product = 0;
        }


        if (current_product > largest_product) {
            largest_product = current_product;
        }

        start++;
        end++;
    }

    printf("The largest product calculated was: %lu\n", largest_product);
    return 0;
}
