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
}

int main(){
    int stat;
    pid_t pid_a, pid_b, pid_m;

    pid_a = fork();
    if (pid_a == 0){
        sleep(10);
        print_pid('a');
        return 10;
    }

    pid_b = fork();
    if (pid_b == 0){
        print_pid('b');
        return 0;
    }

    pid_m = fork();
    if (pid_m == 0){
        sleep(3);
        print_pid('m');
        return 3;
    }

    waitpid(pid_m, &stat, 0);
    printf("El proceso M ha terminado con el status: %d.\n",WEXITSTATUS(stat));

    waitpid(pid_a, &stat, 0);
    printf("El proceso A ha terminado con el status: %d.\n",WEXITSTATUS(stat));

    waitpid(pid_b, &stat, 0);
    printf("El proceso B ha terminado con el status: %d.\n",WEXITSTATUS(stat));



}