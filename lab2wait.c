#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int main(){
    int stat;
    pid_t pid_b, pid_c, pid_e;

    pid_b = fork();
    if (pid_b == 0){
        sleep(3);
        return 1;
    }

    pid_c = fork();
    if (pid_c == 0){
        sleep(1);
        return 2;
    }

    pid_e = fork();
    if (pid_e == 0){
        return 3;
    }

    waitpid(pid_b, &stat, 0);
    printf("El proceso B ha terminado con el status: %d.\n",WEXITSTATUS(stat));

    waitpid(pid_c, &stat, 0);
    printf("El proceso C ha terminado con el status: %d.\n",WEXITSTATUS(stat));

    waitpid(pid_e, &stat, 0);
    printf("El proceso E ha terminado con el status: %d.\n",WEXITSTATUS(stat));



}