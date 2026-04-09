#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void manejador_alarma(int sig) {
    printf("Alarma recibida\n");
   
}

void manejador_sigr1 (int sig){
    printf("Recibí la señal SIGUSR1\n");
    printf("Soy el pid_a\n");
    printf("Mi ID es %d. \n",getpid());
    printf("El ID de mi padre es %d. \n",getppid());
}

void manejador_sigr2 (int sig){
    printf("Recibí la señal SIGUSR2\n");
    printf("Soy el pid_c\n");
    printf("Mi ID es %d. \n",getpid());
    printf("El ID de mi padre es %d. \n",getppid());
}

int main() {
    int stat;
    signal(SIGALRM, manejador_alarma);
   
    pid_t pid_a, pid_c = -1;
    
    
    
    pid_a = fork();
    if (pid_a == 0){
        signal(SIGUSR1,manejador_sigr1);

        pid_c = fork();
        if (pid_c == 0){
        signal(SIGUSR2, manejador_sigr2);
        pause();
        return 0;
        }

        pause();
        kill(pid_c, SIGUSR2);
        printf("Enviando señal al proceso c.\n");
        return 0;
    }

    alarm(3);
    pause();
    printf("Enviando señal al proceso hijo.\n");
    kill(pid_a, SIGUSR1);
    

    

    waitpid(pid_a, &stat, 0);
    waitpid(pid_c, &stat, 0);
    printf("Mis hijos terminaron correctamente %d.\n",WEXITSTATUS(stat));

    

    

    return 0;
}