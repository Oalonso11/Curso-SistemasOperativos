//Programa que obtiene el área de un rectángulo
#include <stdio.h>
int main(void){
    int base;
    int altura;
    int result;
    printf("Ingresa la base del rectangulo: \n");
    scanf("%d", &base);
    printf("Ingresa la altura del rectangulo: \n");
    scanf("%d", &altura);
    result = base * altura;
    printf("El area del rectangulo es: %d\n",result);
    return 0;


}