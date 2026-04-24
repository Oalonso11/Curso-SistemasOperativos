#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex;
int current_i = 0, buffer_index = 0;
int buffer[1000];
#define N_THREADS 1000

void* funcion_hilo(void* arg){

        pthread_mutex_lock (&mutex);
        //Región crítica
        buffer[buffer_index] = current_i;
        buffer_index ++;
        current_i ++;
        //Acaba región
        pthread_mutex_unlock( &mutex ); 
}

int main(){
    //Creamos el mutex
    pthread_mutex_init( &mutex, 0 );

    //Definimos un arreglo para los ids de el hilo
    pthread_t thread_ids[N_THREADS];
    int i;

    //For para crear los 1000 hilos
    for( int i=0; i<N_THREADS; i++)
        pthread_create( &thread_ids[i], NULL, funcion_hilo, NULL );
    
    // Wait for the children to finish.
    for( int i=0; i<N_THREADS; i++)
        pthread_join( thread_ids[i], NULL );


    //Imprimimos donde buffer es 0
    printf("Posiciones donde buffer es 0:\n");
    for (int i=0; i < 1000; i++){
        if (buffer[i] == 0){
            printf("buffer[%d] = 0 \n",i);
        }
    }

    // Destroy the mutex.
    pthread_mutex_destroy( &mutex );
    return 0;

}

