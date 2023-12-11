//Print the type of file where file name accepted through Command Line, give this c program in linux

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct stat file_info;

    if (stat(filename, &file_info) == 0) {
        if (S_ISREG(file_info.st_mode)) {
            printf("%s is a regular file.\n", filename);
        } else if (S_ISDIR(file_info.st_mode)) {
            printf("%s is a directory.\n", filename);
        } else if (S_ISCHR(file_info.st_mode)) {
            printf("%s is a character device.\n", filename);
        } else if (S_ISBLK(file_info.st_mode)) {
            printf("%s is a block device.\n", filename);
        } else if (S_ISFIFO(file_info.st_mode)) {
            printf("%s is a FIFO/pipe.\n", filename);
        } else if (S_ISSOCK(file_info.st_mode)) {
            printf("%s is a socket.\n", filename);
        } else if (S_ISLNK(file_info.st_mode)) {
            printf("%s is a symbolic link.\n", filename);
        } else {
            printf("%s is of unknown type.\n", filename);
        }
    } else {
        perror("stat");
        return 1;
    }

    return 0;
}
