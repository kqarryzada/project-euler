// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
// Find the sum of all the primes below two million.

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include "../lib/numbers.h"


#define LAST_NUM 2000000


int32_t main(void) {
	uint64_t sum = 0;

	for (int32_t i = 2; i < LAST_NUM; i++) {
		if (is_prime(i)) {
			sum += i;
		}

	}

	printf("The sum of all prime numbers up to %u are: %lu\n", LAST_NUM, sum);
}
