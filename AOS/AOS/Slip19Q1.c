//Take multiple files as Command Line Arguments and print their inode number
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // Check if at least one filename is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        exit(1);
    }

    // Loop through each command-line argument (filenames)
    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];
        struct stat file_info;

        // Use stat to get inode information
        if (stat(filename, &file_info) == -1) {
            perror(filename);
        } else {
            printf("File: %s, Inode: %ld\n", filename, (long)file_info.st_ino);
        }
    }

    return 0;
}
