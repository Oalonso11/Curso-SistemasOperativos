#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void manejador_alarma(int sig){
    printf("Alarma recibida\n");
    exit(1);
}

int main(){
    int stat;
    pid_t pid_b, pid_c = -1;

    signal(SIGALRM, manejador_alarma);

    pid_b = fork();
    if(pid_b == 0){
        //poroceso b

        pid_c = fork();
        if(pid_c == 0){
            //proceso c
            while(1){
                printf("Esperando una señal.\n");
                sleep(1);
            }
        }

        sleep(1);
        kill(pid_c, SIGKILL);

        pause();
        return 0;
    }

    alarm(5);
    waitpid(pid_b, &stat, 0);

    return 0;
}