#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>


void signal_handler_sigusr2(int signum) 
{
    int i;
    for (i=0; i<=10;i++){
        printf("La lista impresa es: %d\n",i);
    }
}

int main(){
    pid_t pid_m = -1;
    int i, status;

    pid_m = fork();
    if (pid_m == 0){
        // Proceso hijo
        signal(SIGUSR2, signal_handler_sigusr2);
        printf("Proceso hijo en espera de señales.\n");
        pause();
        return 0;

    }

    printf("Enviando señal al proceso hijo.\n");
    kill(pid_m, SIGUSR2);
    wait(&status);
}