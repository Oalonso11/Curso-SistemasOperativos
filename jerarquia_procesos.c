#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>


void print_pid(char name){
    int numero;
    printf("Soy el %c. \n",name);
    printf("Mi ID es %d. \n",getpid());
    printf("Numero aleatorio: %d\n", numero);
}

int main(){
    srand(time(NULL)); 
    int numero = rand() % 100 + 1;
    int stat;
    pid_t pid_a, pid_b, pid_m;

    pid_a = fork();
    if (pid_a == 0){
        print_pid('a');
        return 0;
    }

     pid_b = fork();
    if (pid_b == 0){
        print_pid('b');
        return 0;
    }

     pid_m = fork();
    if (pid_m == 0){
        print_pid('m');
        return 0;
    }

    wait(&stat);
    printf("Los procesos que terminaron correctamente fueron: %d\n",WEXITSTATUS(stat));
    wait(&stat);
    printf("Los procesos que terminaron correctamente fueron: %d\n",WEXITSTATUS(stat));
    wait(&stat);
    printf("Los procesos que terminaron correctamente fueron: %d\n",WEXITSTATUS(stat));

    




    
}