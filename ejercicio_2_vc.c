#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 1;
int even_turn = 0; //0 impares ; 1 pares

pthread_mutex_t mutex;
pthread_cond_t cond;

void* impares(void* arg)
{
     while(1){
        pthread_mutex_lock( &mutex );

        while (even_turn != 0 && counter <= 100){
        pthread_cond_wait(&cond, &mutex);
     }

     
    
     if (counter > 100){
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        break;
     }

    
   
     printf("Hilo impares: %d\n",counter);
     counter ++;
     even_turn = 1;
    
        
    // Notifica que hay elementos en el buffer
    pthread_cond_signal( &cond);
    pthread_mutex_unlock( &mutex );
    }

    pthread_exit( NULL );
}

void* pares(void* arg)
{
        while(1){
            pthread_mutex_lock( &mutex );
            // ---------- Región crítica
            while (even_turn != 1 && counter <= 100) // Esperar hasta que haya información en el buffer
        {
            // Libera el mutex y espera a que se cumpla la condición (que llegue la señal)
            pthread_cond_wait( &cond, &mutex );
        }

        

        if (counter > 100){
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        printf("Hilo pares: %d\n",counter);
        counter++;

        if (counter > 100){
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
            break;
        }

        even_turn = 0;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock( &mutex );
  }
    

    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_1, thread_2;
    
    pthread_mutex_init( &mutex, 0 );
    pthread_cond_init( &cond, 0 );
    
    // Creamos los hilos
    pthread_create( &thread_1, NULL, impares, NULL );
    pthread_create( &thread_2, NULL, pares, NULL );
    
    pthread_join( thread_1, NULL);
    pthread_join( thread_2, NULL);

    pthread_mutex_destroy( &mutex );
    pthread_cond_destroy( &cond );
    
    return 0;
}

