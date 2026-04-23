#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex;
int acount_a = 1000000, acount_b = 1000000;
#define N_THREADS 1000

void* funcion_hilo(void* arg){
    for(int i=0;i<1000;i++){
        pthread_mutex_lock (&mutex);
        //Región crítica
        acount_a -- ;
        acount_b ++;
        //Acaba región
        pthread_mutex_unlock( &mutex ); 
    }

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

    // Destroy the mutex.
    pthread_mutex_destroy( &mutex );
    printf("\nEl resultado final de a es: %d y el resulatdo final de b es: %d\n",acount_a,acount_b);


}

