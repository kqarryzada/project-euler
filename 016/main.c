// 2^15 = 32768, and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
// What is the sum of the digits of the number 2^1000?

#include <math.h>
#include <inttypes.h>
#include <stdio.h>
#include "../lib/numbers.h"

#define POWER 1000
#define BUFF_SIZE 350


int32_t main(void) {
    char BIG_NUM[BUFF_SIZE];
    // pow() returns a double, but will lose no precision for a power of 2.
    int check = snprintf(BIG_NUM, BUFF_SIZE, "%f\n", pow(2, POWER));
    if (check != 0) {
        fprintf(stderr, "Failed to allocate space.\n");
        return -1;
    }

    uint64_t sum = 0;
    for (int32_t i = 0; i < BUFF_SIZE; i++) {
        if (BIG_NUM[i] == '.') {
            // doubles will print the value with the decimal point. When we reach the decimal point,
            // we've finished the sum calculation.
            break;
        }

        char digit = ascii_to_number(BIG_NUM[i]);
        if (digit == -1) {
            fprintf(stderr, "Error in determining the value.\n");
            return -1;
        }
        sum += digit;
    }

    printf("The sum of the digits of 2^%d is: %lu\n", POWER, sum);
    return 0;
}
