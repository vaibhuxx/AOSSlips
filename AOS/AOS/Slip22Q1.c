/*Write a C Program that demonstrates redirection of standard output to a file.
*/

#include <stdio.h>

int main() {
    // Open a file for writing (or create a new one if it doesn't exist)
    FILE *file = freopen("output.txt", "w", stdout);

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Now, standard output is redirected to the file "output.txt"

    // Print some output
    printf("This is redirected standard output.\n");

    // Close the file (optional)
    fclose(file);

    return 0;
}
