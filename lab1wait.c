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
    printf("Termine mi ejecucion\n");
    printf("Soy el %c. \n",name);
    printf("Mi ID es %d. \n",getpid());
    printf("El ID de mi padre es %d. \n",getppid());
}

int main(){
    pid_t pid_l, pid_d = -1;
    int status;

    pid_l = fork();
    if (pid_l == 0){
        print_pid('L');
        sleep(3);
        
    }

    pid_d = fork();
    if (pid_d == 0){
        print_pid('D');
        sleep(1);
        
    }
    wait (&status);
    printf("Uno de mis hijos ha terminado su ejecucion\n");
    return 0;

}
