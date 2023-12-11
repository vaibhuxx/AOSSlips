/*Write a C program which creates a child process and child process catches a signal
SIGHUP, SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT
signal after every 3 seconds, at the end of 15 second parent send SIGQUIT signal to
child and child terminates by displaying message "My Papa has Killed me!!!”.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void child_signal_handler(int signo) {
    switch (signo) {
        case SIGHUP:
            printf("Child: Received SIGHUP signal.\n");
            break;
        case SIGINT:
            printf("Child: Received SIGINT signal.\n");
            break;
        case SIGQUIT:
            printf("Child: My Papa has killed me!!!\n");
            exit(EXIT_SUCCESS);
            break;
    }
}

int main() {
    pid_t child_pid;

    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("Error creating child process");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process

        // Register signal handlers for SIGHUP, SIGINT, and SIGQUIT
        signal(SIGHUP, child_signal_handler);
        signal(SIGINT, child_signal_handler);
        signal(SIGQUIT, child_signal_handler);

        while (1) {
            // Child process does some work or sleeps
            sleep(1);
        }
    } else {
        // Parent process

        // Send SIGHUP or SIGINT signals to the child every 3 seconds
        for (int i = 0; i < 5; ++i) {
            sleep(3);
            if (i % 2 == 0) {
                printf("Parent: Sending SIGHUP signal to child.\n");
                kill(child_pid, SIGHUP);
            } else {
                printf("Parent: Sending SIGINT signal to child.\n");
                kill(child_pid, SIGINT);
            }
        }

        // After 15 seconds, send SIGQUIT to the child
        sleep(6);
        printf("Parent: Sending SIGQUIT signal to child.\n");
        kill(child_pid, SIGQUIT);

        // Wait for the child to terminate
        wait(NULL);
    }

    return 0;
}
