/*Write a C program to create an unnamed pipe. The child process will write following
three messages to pipe and parent process display it.
Message1 = “Hello World”
Message2 = “Hello SPPU”
Message3 = “Linux is Funny”*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MESSAGE1 "Hello World"
#define MESSAGE2 "Hello SPPU"
#define MESSAGE3 "Linux is Funny"

int main() {
    int pipe_fd[2];
    pid_t child_pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Write three messages to the pipe
        write(pipe_fd[1], MESSAGE1, sizeof(MESSAGE1));
        write(pipe_fd[1], MESSAGE2, sizeof(MESSAGE2));
        write(pipe_fd[1], MESSAGE3, sizeof(MESSAGE3));

        // Close the write end of the pipe
        close(pipe_fd[1]);

        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Read and display messages from the pipe
        char buffer[256];
        int bytesRead;

        while ((bytesRead = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            printf("Parent Process: Received message: %.*s\n", bytesRead, buffer);
        }

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Wait for the child process to finish
        wait(NULL);
    }

    return 0;
}
