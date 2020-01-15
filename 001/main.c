// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9.
// The sum of these multiples is 23. Find the sum of all the multiples of 3 or 5 below 1000.

#include <stdio.h>

int FINAL_NUM = 1000;

int main (void) {
    int sum = 0;
    for (int i = 0; i < FINAL_NUM; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i;
        }
    }
    printf("The sum of all multiples of 3 or 5 up to %d is: %d\n", FINAL_NUM, sum);
}

