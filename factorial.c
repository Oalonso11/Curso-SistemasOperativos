//Programa que encuentra el factorial de un número usando funciones
#include <stdio.h>

   int factorial(int num){
        int factorial;
        int i;
        factorial = 1;
        for (i=1; i<=num; i++){
            factorial *= i;
        }
        return factorial;

    }

int main(){
    int num;
    int i;
    printf("Ingrese un número: ");
    scanf("%d", &num);
      if (num < 0){
            printf("No hay factoriales para negativos\n");
        }
        else{
            int resultado= factorial(num);
            printf("El factorial de %d es: %d",num, resultado);
        }
    
    
    return 0;
}