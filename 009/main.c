// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
// a^2 + b^2 = c^2
// 
// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
// 
// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
// Find the product abc.

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>


#define SUM 1000

// Acquired by simplifying the system of equations. See the comments of compute_system() below
// for the preliminary steps of the derivation.
#define SYSTEM_VALUE 500000


// Solution: Solve the sytem of equations:
// a^2 + b^2 == c^2
// a + b + c == 1000
// 
// ==> a + b + (sqrt(a^2 + b^2)) == 1000
// ==> sqrt(a^2 + b^2) == 1000 - (a + b)
// ==> a^2 + b^2 == (1000 - (a + b))^2
// ...
// ==> 1000a - ab + 1000b == (10^6) / 2 == 500,000
// 
// 
// This method returns true if the values of a and b can solve the system of equations presented
// in the problem.
bool compute_system(int32_t a, int32_t b) {
    return SYSTEM_VALUE == 1000*a - a*b + 1000*b;
}


// Keep plugging in values into the (reduced) system of equations until a solution is found.
int32_t main(void) {
    bool found = false;
    int32_t a, b;

    for (a = 1; a < SUM; a++) {
        // Start b at 'a + 1', given the constraint a < b
        for (b = a + 1; b < SUM; b++) {
            if (compute_system(a, b)) {
                found = true;
                break;
            }
        }

        if (found)
            break;
    }

    if (found) {
        int32_t c = SUM - a - b;
        printf("a = %d, b = %d, and c = %d satisfy the following system of equations:\n", 
                a, b, c);
        printf("-----\n");
        printf("a + b + c = %d\n", SUM);
        printf("a^2 + b^2 = c^2\n");
        printf("-----\n\n");
        printf("The product abc is %d.\n", a * b * c);
        return 0;
    }
    else {
        fprintf(stderr, "No three integers that sum to %d were found such that"
                " a^2 + b^2 = c^2.\n", SUM);
        return -1;
    }
}
