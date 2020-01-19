// A palindromic number reads the same both ways. The largest palindrome made from the product of
// two 2-digit numbers is 9009 = 91 × 99. Find the largest palindrome made from the product of two
// 3-digit numbers.
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/numbers.h"

#define NUM_DIGITS_OF_PRODUCTS 3
#define MAX_PRODUCT pow(10, NUM_DIGITS_OF_PRODUCTS) - 1
#define MIN_PRODUCT pow(10, NUM_DIGITS_OF_PRODUCTS - 1)


int32_t main(void) {
    uint32_t largest_product = 0;
    uint32_t factor1 = 0;
    uint32_t factor2 = 0;

    for (uint32_t a = MAX_PRODUCT; a > MIN_PRODUCT; a--) {
        for (uint32_t b = MAX_PRODUCT; b > MIN_PRODUCT; b--) {
            uint32_t product = a * b;
            if (is_palindrome(product) && product > largest_product) {
                // We've found a new candidate for largest palindrome
                factor1 = a;
                factor2 = b;
                largest_product = product;
            }
        }
    }
    printf("The largest palindrome of two %d-digit numbers is:\n", NUM_DIGITS_OF_PRODUCTS);
    printf("%d x %d = %d\n", factor1, factor2, largest_product);
    return 0;
}
