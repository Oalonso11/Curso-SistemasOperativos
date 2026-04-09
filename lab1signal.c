#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Handler para SIGINT (CTRL + C)
void manejador(int sig) {
 printf(" El usuario presionó CTRL+C\n");
 printf("Pausando 3 segundos...\n");
 sleep(3);
    
}

void salir(int sig) {
    printf("\nPrograma terminado\n");
    exit(0);
}

int main() {
    // Asociar señal SIGINT con el handler
    signal(SIGINT, manejador);
    signal(SIGTSTP, salir); //Ctrl Z
    while (1) {
        printf("\nPID: %d \n",getpid());
        sleep(1);
    }

    return 0;
}