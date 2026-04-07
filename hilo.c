#include <stdio.h>
#include <pthread.h>

void *my_thread_function(void *arg){
    printf("¡Hola desde el hilo!\n");
    pthread_exit (NULL);
}

int main(){
    pthread_t id_thread;
    pthread_create(&id_thread,NULL,my_thread_function,NULL);
    pthread_join(id_thread,NULL);
    printf("El hilo ha terminado. \n");
    return 0;
}