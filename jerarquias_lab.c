#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

void verificado(int num){
    if (num < 0){
        if (errno == EAGAIN){
            printf("Archivo bloqueado. \n");
            exit(1);
        }

        else if (errno == EACCES){
            printf("Problema de permisos del archivo.\n");
            exit(1);
        }

        else if (errno == EBADF){
            printf("Mal descriptor del archivo.\n");
            exit(1);
        }

        else{
             perror("Error: \n");
             exit(1);
        }
    }

}

void print_pid(char name){
    printf("Soy el %c. \n",name);
    printf("Mi ID es %d. \n",getpid());
    printf("El ID de mi padre es %d. \n\n",getppid());
}

int main(){
    pid_t pid_T, pid_W, pid_V, pid_S, pid_L, pid_P =-1;

    pid_T = fork();
    if (pid_T == 0){
        print_pid('T');
        exit(0);
    }
    
    pid_W = fork();
    if (pid_W == 0){
        print_pid('W');
        exit(0);
    }

}