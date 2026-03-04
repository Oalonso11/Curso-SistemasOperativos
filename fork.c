#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
    pid_t pid = -1;
    int x=5,y=10;

    pid = fork();

    //Código del hijo
    if ( pid == 0){
       int x =x+10;
       int y=y+6;

        printf("Soy el hijo  y la suma es: y mi pid =  %d,%d,%d\n",x,y, getpid());
        exit(0);
    }

    //Código del padre (el hijo terminó en exit)
    printf("Soy el padre y mi pid = %d\n", getpid());

    return 0;
}