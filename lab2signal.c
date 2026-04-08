#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void manejador_alarma(int sig) {
    printf("Transcurrieron 3 segundos\n");
   
}

int main() {
    signal(SIGALRM, manejador_alarma);
    alarm(3);

    while (1) {
        pause(); 
    }

    return 0;
}