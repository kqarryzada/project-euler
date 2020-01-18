// The sum of the squares of the first ten natural numbers is: 1^2+2^2+...+10^2=385.
// The square of the sum of the first ten natural numbers is: (1+2+...+10)^2=552=3025.
// Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025−385=2640.
// Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

#include <inttypes.h>
#include <stdio.h>

#define N 100

int main(void) {
    // Find sum of squares first. Note that:
    // (∑(n^2))^2 = (n(n + 1)/2) ^ 2
    uint64_t sum_of_squares = N * (N + 1) / 2;
    sum_of_squares = sum_of_squares * sum_of_squares;
    printf("%lu\n", sum_of_squares);

    // Find square of sums. Note that:
    // (∑(n))^2 = n(n + 1)(2n + 1)/6
    uint64_t square_of_sums = N * (N + 1) * (2 * N + 1) / 6;
    printf("%lu\n", square_of_sums);

    printf("(∑(%d))^2 - ∑(%d^2) = %lu\n.", N, N, sum_of_squares - square_of_sums);
}
