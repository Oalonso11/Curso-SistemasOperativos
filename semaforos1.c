#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int active_connections= 0;
#define N_THREADS 10
// Declare the semaphore as a global variable so that the threads can use it.
sem_t semaphore_id;

void* base_datos(void* arg) 
{
        sem_wait( &semaphore_id );
        active_connections++;
        printf("\nEl numero de conexiones activas es: %d",active_connections);
        sleep(1);
        active_connections--;

        //Libera el semáforo
        sem_post( &semaphore_id );
    
    pthread_exit( NULL );
}

int main() 
{
    pthread_t thread_ids[N_THREADS];
    
    // Create the semaphore.
    sem_init(&semaphore_id,0,3);
    // Create children.
    for( int i=0; i<N_THREADS; i++)
        pthread_create( &thread_ids[i], NULL,base_datos, NULL );
    
    // Wait for the children to finish.
    for( int i=0; i<N_THREADS; i++)
        pthread_join( thread_ids[i], NULL );
    
    // Destroy the semaphore.
    sem_destroy( &semaphore_id );
    printf("\nEl valor final del conexiones activas es: %d\n", active_connections);
    return 0;
}