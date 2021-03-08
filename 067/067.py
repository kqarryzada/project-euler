#!/usr/bin/env python3
"""
Maximum path sum II

This is a much more difficult version of Problem 18. It is not possible to try every route to solve
this problem, as there are 299 altogether! If you could check one trillion (1012) routes every
second it would take over twenty billion years to check them all. There is an efficient algorithm to
solve it. ;o)
"""


# The file containing the triangle data.
FILENAME = "p067_triangle.txt"

TRIANGLE_WIDTH = 100


def compute_max_sum(matrix):
    """Computes the max path sum problem.

    :param matrix: A lower-triangular matrix containing the triangle data.
    :return: The maximum possible sum achieved by traversing the tree.
    """

    depth = len(matrix)
    for row in range(depth - 1, 0, -1):
        for i in range(row):
            left = matrix[row][i]
            right = matrix[row][i + 1]

            larger_child_val = left if left > right else right
            matrix[row - 1][i] += larger_child_val

    return matrix[0][0]


def main():
    width = TRIANGLE_WIDTH

    matrix = []
    with open(FILENAME, "r") as file:
        line = file.readline()
        while line:
            row_list = line.strip().split(" ")
            if len(row_list) > width:
                print("Read a line from the file, {}, that had more numbers than the"
                      " expected width, {}.".format(FILENAME, width))
                print("The line contained:")
                print(line)
                exit(1)

            # Replace String values with integers.
            row_list = [int(x) for x in row_list]

            # Mark the remaining elements in the row as zero to create a square matrix. For
            # example, the first row only has one entry, so if the width is 100, add 99 zeroes
            # to this row to make it a square matrix.
            for i in range(len(row_list), width):
                row_list.append(0)

            matrix.append(row_list)
            line = file.readline()

    total_sum = compute_max_sum(matrix)
    print("The sum for the {}-line matrix is {}.".format(len(row_list), total_sum))


if __name__ == "__main__":
    main()
