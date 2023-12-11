/*Read the current directory and display the name of the files, no of files in current
directory*/

#include <stdio.h>
#include <dirent.h>

void listFiles() {
    DIR *dir;
    struct dirent *entry;
    int fileCount = 0;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    // Iterate through each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a regular file
        if (entry->d_type == DT_REG) {
            printf("%s\n", entry->d_name);
            fileCount++;
        }
    }

    // Close the directory
    closedir(dir);

    // Display the total number of files
    printf("Total number of files: %d\n", fileCount);
}

int main() {
    // Call the function to list files in the current directory
    listFiles();

    return 0;
}
