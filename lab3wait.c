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
    printf("Soy el %c. \n",name);
    printf("Mi ID es %d. \n",getpid());
    printf("El ID de mi padre es %d. \n",getppid());
}

int  main(){
    int stat;
    pid_t pid_a, pid_b, pid_c, pid_d = -1;

    pid_a = fork();
    if (pid_a == 0){
        print_pid('A');
        waitpid(pid_d, &stat, 0);
        printf("El proceso B ha terminado con el status: %d.\n",WEXITSTATUS(stat));
        execl("/bin/rm","rm","-d","new_folder",NULL);

     pid_d = fork();
        if (pid_d == 0){
        print_pid('D');
        execl("/bin/ls","ls",NULL);
        return 2;
        }
        return 1;
    } 

    pid_b = fork();
    if (pid_b == 0){
        print_pid('B');
        execl("/bin/mkdir","mkdir","new_folder",NULL);
        return 3;
    }

    pid_c = fork();
    if (pid_c == 0){
        print_pid('C');
        execl("/bin/ls","ls",NULL);
        return 4;
        
    }

    waitpid(pid_a, &stat, 0);
    printf("El proceso A ha terminado con el status: %d.\n",WEXITSTATUS(stat));

    waitpid(pid_c, &stat, 0);
    printf("El proceso C ha terminado con el status: %d.\n",WEXITSTATUS(stat));

    waitpid(pid_b, &stat, 0);
    printf("El proceso B ha terminado con el status: %d.\n",WEXITSTATUS(stat));

    print_pid('M');
    execl("/bin/ls","ls",NULL);

    
    


    

}