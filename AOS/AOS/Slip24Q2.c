/*Write a C program which creates a child process to run linux/ unix command or any
user defined program. The parent process set the signal handler for death of child
signal and Alarm signal. If a child process does not complete its execution in 5
second then parent process kills child process.*/


#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include<sys/wait.h>
#include <sys/types.h>

void sig_handler(int signo)
{
    int status;
    waitpid(-1,&status,WNOHANG);
}

void alm_handler(int signo)
{
    printf("Parent: Clid process took too long,killing it");
    kill(getpid(),SIGKILL);
}

int main(int argc, char **argv )
{
    pid_t pid;
    int status;
    signal (SIGCHLD, sig_handler);
    signal(SIGALRM,alm_handler);

    alarm(5);
    pid=fork();

    if(pid<0)
    {
        perror("Fork faild");
        exit(EXIT_FAILURE);

    }
    else if (pid==0) {
        printf("Child: Running the cmd\n");
        execlp("ls","ls",(char *)NULL);
        perror("Exex Failed");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Parent: Waiting for the child process...\n");
        waitpid(pid,&status,0);
        printf("Parent:Child process completed\n");
        alarm(0);
    }
    return 0;
}

