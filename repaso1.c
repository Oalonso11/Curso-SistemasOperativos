#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int factorial(int n){
        int factorial;
        int i;
        factorial = 1;
        for (i=1; i<=n; i++){
            factorial *= i;
        }
        return factorial;

    }

int main(){
    int status;
    int n = 5;
    int m = 3;
    int resta = n-m;
    int resultado1, resultado2, resultado3;
    pid_t pid_d,pid_b,pid_c = -1;
    
    pid_b = fork();
    if (pid_b == 0){
        resultado1 = factorial(resta);
        return resultado1;
    }

    pid_c = fork();
    if (pid_c == 0){
        resultado2 = factorial(m);
        return resultado2;
    }

    pid_d = fork();
    if (pid_d == 0){
        resultado3 = factorial(n);
        return resultado3;
    }

    waitpid(pid_b, &status, 0);
    printf("El proceso M ha terminado con el status: %d.\n",WEXITSTATUS(status));
    int resultadohijo_b = WEXITSTATUS(status);
    waitpid(pid_c, &status, 0);
    printf("El proceso A ha terminado con el status: %d.\n",WEXITSTATUS(status));
    int resultadohijo_c = WEXITSTATUS(status);
    waitpid(pid_d, &status, 0);
    printf("El proceso B ha terminado con el status: %d.\n",WEXITSTATUS(status));
    int resultadohijo_d = WEXITSTATUS(status);
    int resultado4 = resultadohijo_d/(resultadohijo_c* resultadohijo_b);
    printf("El resultado de la formula es: %d",resultado4);







}