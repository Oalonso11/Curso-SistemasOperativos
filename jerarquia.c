#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

void print_pid(char name){
    printf("Soy el %c. \n",name);
    printf("Mi ID es %d. \n",getpid());
    printf("El ID de mi padre es %d. \n\n",getppid());
}

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

int main(){
    int valor;
    int fd,m,n,i;
    int arreglor [5] = {1,2,3,4,5};
    pid_t pid_m = -1;
    pid_m = fork();
    

    if (pid_m == 0){
        print_pid('M');
        fd = creat("datos.txt",0777);
        verificado(fd);
        n = write(fd, &arreglor, sizeof(arreglor));
        verificado(n);
        close(fd);

        exit(0);
    }
    sleep(3);

   
    fd = open("datos.txt",0);
    m = read( fd, &arreglor, sizeof(arreglor));
    verificado(m);
    printf("%d \n",m);
    close(fd);
    n = m/sizeof(int);
    
    printf("Los enteros incluidos en el archivo datos.txt son: ");
    for (i = 0; i <n; i++){
        printf(" %d, ",arreglor[i]);
        
    }

    return 0;

}