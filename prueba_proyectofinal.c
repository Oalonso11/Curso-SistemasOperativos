#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

#define MAX_PALABRAS 100
#define MAX_TAM 100
#define MAX_CAMBIOS 10

char palabras[MAX_PALABRAS][MAX_CAMBIOS][MAX_TAM];
char pistas[MAX_PALABRAS][MAX_CAMBIOS][MAX_TAM];

int contestadas[MAX_PALABRAS];
int cambioActual[MAX_PALABRAS];
int cantidadCambios[MAX_PALABRAS];

int i = 0;
int totalPalabras = 0;

// Para quitar el salto de linea de fgets
void quitarSalto(char texto[]){
    int j = 0;

    while (texto[j] != '\0'){

        if (texto[j] == '\n'){
            texto[j] = '\0';
            break;
        }

        j++;
    }
}

// Leemos las palabras desde palabras.txt
void leerPalabras(){
    FILE *archivo;
    char linea[MAX_TAM];
    int cambio = 0;

    archivo = fopen("palabras.txt","r");

    if (archivo == NULL){
        printf("No se pudo abrir el archivo palabras.txt\n");
        exit(1);
    }

    totalPalabras = 0;
    cambio = 0;

    while(fgets(linea, MAX_TAM, archivo) != NULL){
        quitarSalto(linea);

        // Linea vacia significa que empieza otro grupo
        if(linea[0] == '\0'){
            if(cambio > 0){
                cantidadCambios[totalPalabras] = cambio;
                contestadas[totalPalabras] = 0;
                cambioActual[totalPalabras] = 0;
                totalPalabras++;
                cambio = 0;
            }
        }
        else{
            strcpy(palabras[totalPalabras][cambio], linea);
            cambio++;
        }
    }

    // Guardar el ultimo grupo si no termina con linea vacia
    if(cambio > 0){
        cantidadCambios[totalPalabras] = cambio;
        contestadas[totalPalabras] = 0;
        cambioActual[totalPalabras] = 0;
        totalPalabras++;
    }

    fclose(archivo);
}

// Leer pistas desde pistas.txt
void leerPistas(){
    FILE *archivo;
    char linea[MAX_TAM];
    int palabra = 0;
    int cambio = 0;

    archivo = fopen("pistas.txt", "r");

    if (archivo == NULL){
        printf("No se pudo abrir pistas.txt \n");
        exit(1);
    }

    palabra = 0;
    cambio = 0;

    while(fgets(linea, MAX_TAM, archivo) != NULL && palabra < totalPalabras){
        quitarSalto(linea);

        // Linea vacia significa que empieza otro grupo de pistas
        if(linea[0] == '\0'){
            palabra++;
            cambio = 0;
        }
        else{
            strcpy(pistas[palabra][cambio], linea);
            cambio++;
        }
    }

    fclose(archivo);
}

// Revisa si todas ya fueron contestadas
int todasContestadas(){
    int j;

    for (j = 0; j < totalPalabras; j++){
        if (contestadas[j] == 0){
            return 0;
        }
    }

    return 1;
}

// Avanza a la siguiente palabra que no haya sido contestada
void siguientePalabra(){
    int vueltas = 0;

    do{
        i = (i + 1) % totalPalabras;
        vueltas++;
    }
    while(contestadas[i] == 1 && vueltas <= totalPalabras);
}

// Mostrar pistas
void mostrar(){
    printf("\nPalabra numero %d\n", i + 1);
    printf("Pista: %s\n", pistas[i][cambioActual[i]]);
    printf("Longitud: %d letras\n", (int)strlen(palabras[i][cambioActual[i]]));
}

// Cambia la palabra actual y despues muestra
void Palabra(int sig){
    if(todasContestadas() == 1){
        return;
    }

    if(contestadas[i] == 0){
        cambioActual[i] = (cambioActual[i] + 1) % cantidadCambios[i];

        printf("\nCambio de palabra por tiempo\n");
        mostrar();
    }

    alarm(20);
}

// Compara sin distinguir mayusculas y minusculas
int comparar(char intento[], char correcta[]){
    int j = 0;

    while(intento[j] != '\0' && correcta[j] != '\0'){
        if(tolower(intento[j]) != tolower(correcta[j])){
            return 0;
        }

        j++;
    }

    if(intento[j] != correcta[j]){
        return 0;
    }

    return 1;
}

int main(){
    leerPalabras();
    leerPistas();

    if(totalPalabras == 0){
        printf("No hay palabras cargadas\n");
        return 0;
    }

    signal(SIGALRM, Palabra);

    mostrar();   // primera pista inmediata
    alarm(25);

    int numero;
    char intento[MAX_TAM];

    while(1){
        if(todasContestadas() == 1){
            printf("\nGanaste, adivinaste todas las palabras\n");
            break;
        }

        printf("\nEscribe numero y palabra: ");
        scanf("%d %s", &numero, intento);

        numero = numero - 1;

        if(numero < 0 || numero >= totalPalabras){
            printf("Ese numero de palabra no existe\n");
        }
        else if(contestadas[numero] == 1){
            printf("Esa palabra ya fue contestada\n");
        }
        else{
            if(comparar(intento, palabras[numero][cambioActual[numero]]) == 1){
                printf("Correcto\n");
                contestadas[numero] = 1;

                if(todasContestadas() == 1){
                    printf("\nGanaste, adivinaste todas las palabras\n");
                    break;
                }

                i = numero;
                siguientePalabra();
                mostrar();
            }
            else{
                printf("Incorrecto\n");
                i = numero;
                mostrar();
            }
        }
    }

    return 0;
}