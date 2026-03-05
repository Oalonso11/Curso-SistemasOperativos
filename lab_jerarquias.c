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

int main(){
    int fd,m,n,i;
    pid_t pid_n, pid_m = -1;

    pid_n = fork();
     if (pid_n == 0){
        fd = creat("N.txt",0777);
        verificado(fd);
        int arreglo_pares[10] = {2,4,6,8,10,12,14,16,18,20};
        n = write(fd, &arreglo_pares, sizeof(arreglo_pares));
        verificado(n);
        close(fd);

        exit(0);
    }

    pid_m = fork();
     if (pid_m == 0){
        fd = creat("M.txt",0777);
        verificado(fd);
        int arreglo_impares[10] = {1,3,5,7,9,11,13,15,17,19};
        n = write(fd, &arreglo_impares, sizeof(arreglo_impares));
        verificado(n);
        close(fd);

        exit(0);
    }

    int arreglo_pares[10];
    int arreglo_impares[10];

    sleep(3);
    fd = open("N.txt",0);
    m = read( fd, &arreglo_pares, sizeof(arreglo_pares));
    verificado(m);
    printf("%d \n",m);
    close(fd);
    n = m/sizeof(int);
    
    printf("El arreglo de numeros enteros incluido en el N.txt es: ");
    for (i = 0; i <n; i++){
        printf(" %d, ",arreglo_pares[i]);
        
    }

    //Arreglo números impares
    fd = open("M.txt",0);
    m = read( fd, &arreglo_impares, sizeof(arreglo_impares));
    verificado(m);
    close(fd);
    n = m/sizeof(int);

    
    printf("\nEl arreglo de numeros impares incluido en el M.txt es: ");
    for (i = 0; i <n; i++){
        printf(" %d, ",arreglo_impares[i]);
        
    }

    int suma;
    for (i=0; i<n; i++){
        suma= arreglo_pares[i] + arreglo_impares[i];
        printf("\nLa suma de las posiciones de los arreglos es %d + %d = %d ",arreglo_pares[i],arreglo_impares[i],suma);
    }
    
    return 0;

}