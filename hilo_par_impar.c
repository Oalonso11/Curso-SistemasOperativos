#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS_NO 10

/* Print hello world and kill the thread. */
void *par( void *args )
{
    printf( "Soy par.\n" );
    pthread_exit( NULL );
}

void *impar( void *args )
{
    printf( "Soy impar.\n" );
    pthread_exit( NULL );
}




int main()
{
    pthread_t id_threads[THREADS_NO];
    int state, i;
    
    for(i=0; i < THREADS_NO; i++) 
    {

        if (i%2 == 0){
        pthread_create( &id_threads[i], NULL,par, NULL );
        } 
        else{
            pthread_create( &id_threads[i], NULL,impar, NULL );
        }
    }

    
    
    pthread_join(id_threads[i],NULL);

    exit(0);
}