// A palindromic number reads the same both ways. The largest palindrome made from the product of
// two 2-digit numbers is 9009 = 91 × 99. Find the largest palindrome made from the product of two
// 3-digit numbers.
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_DIGITS_OF_PRODUCTS 3
#define MAX_PRODUCT pow(10, NUM_DIGITS_OF_PRODUCTS) - 1
#define MIN_PRODUCT pow(10, NUM_DIGITS_OF_PRODUCTS - 1)


bool is_palindrome(int32_t num) {
    bool retval = true;
    // Convert 'num' to string
    char* num_string = malloc(sizeof(char) * 10);
    sprintf(num_string, "%d", num);

    // 'n' is the index of the last element of the string
    int32_t n = strlen(num_string) - 1;
    for (int32_t i = 0; i <= n / 2; i++) {
        if(num_string[i] != num_string[n - i]) {
            retval = false;
            break;
        }
    }

    free(num_string);
    return retval;
}


int main(void) {
    int32_t largest_product = 0;
    int32_t factor1 = 0;
    int32_t factor2 = 0;

    for (int32_t a = MAX_PRODUCT; a > MIN_PRODUCT; a--) {
        for (int32_t b = MAX_PRODUCT; b > MIN_PRODUCT; b--) {
            int32_t product = a * b;
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
