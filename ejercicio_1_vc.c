#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int key_1 = 0, key_2 = 0;

pthread_mutex_t mutex;
pthread_cond_t condicion;

void* key1(void* arg)
{
    
    pthread_mutex_lock( &mutex );
     
    key_1 = 1;
    printf("Cambié la llave k1 de valor a 1.\n");
        
    // Notifica que hay elementos en el buffer
    pthread_cond_signal( &condicion );
    pthread_mutex_unlock( &mutex );
    

    pthread_exit( NULL );
}

void* key2(void* arg)
{
    
        pthread_mutex_lock( &mutex );
        // ---------- Región crítica
        while (key_1 =! 1) // Esperar hasta que haya información en el buffer
        {
            // Libera el mutex y espera a que se cumpla la condición (que llegue la señal)
            pthread_cond_wait( &condicion, &mutex );
        }
        key_2 = 1;
        printf("Cambié la variable key 2 a valor 1.\n");
        

        pthread_mutex_unlock( &mutex );
        
    

    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_1, thread_2;
    
    pthread_mutex_init( &mutex, 0 );
    pthread_cond_init( &condicion, 0 );
    
    // Creamos los hilos
    pthread_create( &thread_1, NULL, key1, NULL );
    pthread_create( &thread_2, NULL, key2, NULL );
    
    pthread_join( thread_1, NULL);
    pthread_join( thread_2, NULL);

    printf("Llaves sincronizadas, cohete lanzado en 3... 2... 1... Cohete lanzado correctamente\n");

    pthread_mutex_destroy( &mutex );
    pthread_cond_destroy( &condicion );
    
    return 0;
}

