// 5 Write a C program to find whether a given file is present in current directory or not.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    // Use the access function to check if the file exists
    if (access(filename, F_OK) == 0) {
        printf("File '%s' exists in the current directory.\n", filename);
    } else {
        printf("File '%s' does not exist in the current directory.\n", filename);
    }

    return 0;
}
