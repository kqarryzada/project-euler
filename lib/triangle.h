// This file contains functions that are related to computations on lower-triangular matrices.
//
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <inttypes.h>

#endif



/**
 * Computes the largest possible sum that can be achieved by traversing the
 * tree/triangle buffer from a node to another adjacent node. For example, in
 * the following triangle:
 * { 3, 0, 0, 0 }
 * { 7, 4, 0, 0 }
 * { 2, 4, 6, 0 }
 * { 8, 5, 9, 3 }
 *
 * 3's children are 7 and 4 underneath it, 7's children are 2 and 4 underneath
 * it, etc. The largest possible sum by travelling from parent to child, until
 * reaching the bottom of the tree, is achieved by taking the path 3 -> 7 -> 4
 * -> 9, to achieve a sum of 23.
 *
 * The input triangle must be stored as a lower-triangular matrix as in the
 * example above (i.e., the top half should be padded with zeros).
 *
 * This function will overwrite the data in the triangle buffer. It completes in
 * O(n) time, where n is the number of elements in the buffer.
 *
 * @param depth     The depth of the triangle (i.e., the number of rows).
 * @param triangle  A pointer to the buffer containing the triangle.
 *
 * @return          The largest sum obtained by traversing adjacent numbers,
 *					or -1 if there was an issue.
 */
int32_t compute_max_sum(uint32_t depth, uint32_t width, int32_t triangle[depth][width]);
