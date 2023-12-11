/*
Write a C program that redirects standard output to a file output.txt. (use of dup and
open system call).*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open a file for writing (or create a new one if it doesn't exist)
    int file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (file == -1) {
        perror("Error opening file");
        return 1;
    }

    // Duplicate the file descriptor for standard output (stdout)
    int saved_stdout = dup(fileno(stdout));

    // Redirect standard output to the file
    if (dup2(file, fileno(stdout)) == -1) {
        perror("Error redirecting standard output");
        close(file);
        return 1;
    }

    // Now, standard output is redirected to the file "output.txt"

    // Print some output
    printf("This is redirected standard output using dup and open system calls.\n");

    // Flush the output to make sure it is written to the file
    fflush(stdout);

    // Close the file descriptor and restore the original stdout
    close(file);
    dup2(saved_stdout, fileno(stdout));
    close(saved_stdout);

    return 0;
}
