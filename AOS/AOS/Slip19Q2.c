/*Implement the following unix/linux command (use fork, pipe and exec system call)
ls –l | wc –l*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Redirect stdin to read from the pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        // Close the read end of the pipe (not needed anymore)
        close(pipe_fd[0]);

        // Execute the "wc -l" command
        execlp("wc", "wc", "-l", (char *)NULL);

        // If execlp fails
        perror("Error executing wc");
        exit(EXIT_FAILURE);
    } else {
        // Parent process

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Redirect stdout to write to the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Close the write end of the pipe (not needed anymore)
        close(pipe_fd[1]);

        // Execute the "ls -l" command
        execlp("ls", "ls", "-l", (char *)NULL);

        // If execlp fails
        perror("Error executing ls");
        exit(EXIT_FAILURE);
    }

    // Wait for the child process to finish
    wait(NULL);

    return 0;
}
