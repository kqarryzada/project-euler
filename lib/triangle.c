#include <stdio.h>
#include "triangle.h"



int32_t compute_max_sum(uint32_t depth, uint32_t width, int32_t triangle[depth][width]) {
    if(triangle[0][0] == 0) {
        fprintf(stderr, "A triangle with root value zero was detected. The triangle was likely"
               " padded incorrectly.\n");
        return -1;
    }

    // Start at the bottom row, and take the numbers two at a time. These two children share one
    // parent. For this miniature tree of three nodes, (i.e., two parents and one child), the larger
    // child will always be the path taken. Thus, take the larger value and add it to the common
    // parent between these two, overwriting the parent's value. Repeat this until the row is
    // finished.
    //
    // When the bottom row is finished modifying its parent row, this parent row will contain the
    // largest possible sum for the row beneath it. Repeat this process, again collapsing the
    // largest possibilities of this row into its own parent.
    //
    // Repeat this until the top of the triangle is reached.
    for(int32_t row = depth - 1; row > 0; row--) {
        int32_t numElementsInRow = row + 1;
        for(int32_t i = 0; i < numElementsInRow; i++) {
            int32_t left = triangle[row][i];
            int32_t right = triangle[row][i + 1];

            // Increment the parent by the larger value, overwriting its data with the largest
            // possible sum for the entries beneath it.
            triangle[row - 1][i] += (left > right) ? left : right;
        }
    }

    // When the loop completes, the root of the triangle will contain the largest
    // possible sum.
    return triangle[0][0];
}
