#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex;

void* increase_counter(void* arg) 
{
    int i;
    for ( int i=0; i<100; i++) 
    {
        pthread_mutex_lock( &mutex ); 
        // ---------- Critical region.
        counter++;
        // ---------- En of the critical region.
        pthread_mutex_unlock( &mutex ); 
    }
    pthread_exit( NULL );
}

int main() 
{
    pthread_t thread_1, thread_2;
    
    // Create the mutex.
    pthread_mutex_init( &mutex, 0 );
    
    pthread_create(&thread_1, NULL, increase_counter, NULL);
    pthread_create(&thread_2, NULL, increase_counter, NULL);
    
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    
    // Destroy the mutex.
    pthread_mutex_destroy( &mutex );
    
    printf("El valor final del contador es %d\n", counter);
    return 0;
}