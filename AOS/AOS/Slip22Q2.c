/*Write a C program to implement the following unix/linux command (use fork, pipe and exec system call). Your program should block the signal Ctrl-C and Ctrl-\ signal
during the execution. i. Ls –l | wc –l*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sig_handler(int signo) {
    // Signal handler to do nothing
}

int main() {
    pid_t child1_pid, child2_pid;
    int pipe_fd[2];

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }

    // Create the first child process (ls -l)
    if ((child1_pid = fork()) == -1) {
        perror("Error creating first child process");
        exit(EXIT_FAILURE);
    }

    if (child1_pid == 0) {
        // Child process 1

        // Set up signal handler to block signals
        signal(SIGINT, sig_handler);
        signal(SIGQUIT, sig_handler);

        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Execute the "ls -l" command
        execlp("ls", "ls", "-l", (char *)NULL);

        // If execlp fails
        perror("Error executing ls");
        exit(EXIT_FAILURE);
    }

    // Create the second child process (wc -l)
    if ((child2_pid = fork()) == -1) {
        perror("Error creating second child process");
        exit(EXIT_FAILURE);
    }

    if (child2_pid == 0) {
        // Child process 2

        // Set up signal handler to block signals
        signal(SIGINT, sig_handler);
        signal(SIGQUIT, sig_handler);

        // Redirect stdin to read from the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Execute the "wc -l" command
        execlp("wc", "wc", "-l", (char *)NULL);

        // If execlp fails
        perror("Error executing wc");
        exit(EXIT_FAILURE);
    }

    // Close both ends of the pipe in the parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    waitpid(child1_pid, NULL, 0);
    waitpid(child2_pid, NULL, 0);

    return 0;
}
