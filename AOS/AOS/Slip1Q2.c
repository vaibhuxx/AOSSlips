/*User
Write a C program to send SIGALRM signal by child process to parent process and
parent process make a provision to catch the signal and display alarm is fired.(Use
Kill, fork, signal and sleep system call)*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void alarm_handler(int signo) {
    if (signo == SIGALRM) {
        printf("Parent: Alarm is fired!\n");
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

        // Sleep for 3 seconds
        sleep(3);

        // Send SIGALRM signal to the parent process
        kill(getppid(), SIGALRM);

        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        // Register the signal handler for SIGALRM
        signal(SIGALRM, alarm_handler);

        // Wait for the child to terminate
        wait(NULL);

        printf("Parent: Child process has terminated.\n");
    }

    return 0;
}
