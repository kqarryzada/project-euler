// The prime factors of 13195 are 5, 7, 13 and 29.

// What is the largest prime factor of the number 600851475143?

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_INPUT 600851475143

bool isNumber(char* value) {
    char* ptr = value;
    while (*ptr != 0) {
        if (!isdigit(*ptr)) {
            return false;
        }
        ptr++;
    }

    // Went through whole string, and all were digits
    return true;

}



int main(int argc, char** argv) {
    uint64_t value;
    if (argc == 1) {
        value = DEFAULT_INPUT;
    }
    else if (argc == 2) {
        char* input = argv[1];
        if (!isNumber(input)) {
            fprintf(stderr, "'%s' is not a valid number.\n", input);
            return -1;
        }

        sscanf(argv[1], "%ld", &value);
        if (value == 0) {
            fprintf(stderr, "0 is not a valid input.\n");
            return -1;
        }
    }
    else {
        fprintf(stderr, "Invalid number of parameters detected.\n");
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return -1;
    }
    printf("value is %ld\n", value);
}
