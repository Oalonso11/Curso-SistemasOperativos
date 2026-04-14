#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int parte_uno, parte_dos ,parte_tres;
int resultado_uno, resultado_dos, resultado_tres;

void *factorial_1( void *args )
{
     int factorial_1;
        int i;
        factorial_1 = 1;
        for (i=1; i<=parte_uno; i++){
            factorial_1 *= i;
        }
        resultado_uno = factorial_1;
        printf("\nMi factorial es: %d\n",resultado_uno);

    pthread_exit( NULL );

}

void *factorial_2( void *args )
{
    int factorial_2;
        int i;
        factorial_2 = 1;
        for (i=parte_uno +1; i<=parte_dos; i++){
            factorial_2 *= i;
        }
        resultado_dos = factorial_2;

        printf("\nMi factorial es: %d\n",resultado_dos);

    pthread_exit( NULL );

}

void *factorial_3( void *args )
{
    int factorial_3;
        int i;
        factorial_3 =1;
        for (i=parte_dos+1; i<=parte_tres; i++){
            factorial_3 *= i;
        }

        resultado_tres = factorial_3;

        printf("\nMi factorial es: %d\n",resultado_tres);

    pthread_exit( NULL );
}

int main(){
    int num,x; 
    printf("Ingrese un numero: ");
    scanf("%d", &num);

    parte_uno = num /3;
    parte_dos = num/3*2;
    parte_tres = num;

    if (num % 3 == 0){
        printf("El número es divisible entre 3\n");
        pthread_t fact_1,fact_2,fact_3;
        pthread_create(&fact_1,NULL,factorial_1,NULL);
        pthread_join(fact_1,NULL);
        printf("El hilo 1 ha terminado. \n");

        pthread_create(&fact_2,NULL,factorial_2,NULL);
        pthread_join(fact_2,NULL);
        printf("El hilo 2 ha terminado. \n");

        pthread_create(&fact_3,NULL,factorial_3,NULL);
        pthread_join(fact_3,NULL);
        printf("El hilo 3 ha terminado. \n");

        int factorial_final = resultado_uno*resultado_dos*resultado_tres;
        printf("El factorial de %d es: %d\n",num,factorial_final);

    }
    else{
        printf("El numero no es divisible entre 3");
    }

   

}