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
    int n,m,fd,i;
    float arreglo[3] = {4.6,5.1,6.8};
    float arreglor[3];
    float valor;
    fd = creat("archivo.txt",0777);
    verificado(fd);

    n = write(fd, &arreglo, sizeof(arreglo));
    verificado(n);
    close(fd);

    fd = open("archivo.txt",0);
    m = read( fd, &arreglor, sizeof(arreglor));
    verificado(m);
    printf("%d \n",m);
    close(fd);
    n = m/sizeof(float);

    printf("El arreglo de flotantes es:");
    for (i=0; i < n; i++){
        printf(" %.2f ",arreglor[i]);
    }

    fd = creat("datos2.txt",0777);
    verificado(fd);

    valor = 23.4;
    n = write(fd, &valor, sizeof(valor));
    verificado(n);
    printf("\nEl valor de n para el primer flotante es: %d\n",n);

    valor = 28.47;
    n = write(fd, &valor, sizeof(valor));
    verificado(n);
    printf("El valor de n para el segundo flotante es: %d\n",n);

    valor = 20.67;
    n = write(fd, &valor, sizeof(valor));
    verificado(n);
    printf("El valor de n para el tercer flotante es: %d\n",n);

    valor = 67.67;
    n = write(fd, &valor, sizeof(valor));
    verificado(n);
    printf("El valor de n para el cuarto flotante es: %d\n",n);

    valor = 13.32;
    n = write(fd, &valor, sizeof(valor));
    verificado(n);
    printf("El valor de n para el quinto flotante es: %d\n",n);
    close(fd);

    float arregloaux[5];

    fd = open("datos2.txt",0);
    m = read( fd, &arregloaux, sizeof(arregloaux));
    verificado(m);
    printf("%d \n",m);
    close(fd);
    n = m/sizeof(float);
    
    printf("Los flotantes incluidos en el archivo datos2.txt son: ");
    for (i = 0; i <n; i++){
        printf(" %.2f ",arregloaux[i]);
        
    }
    
    return 0;

}