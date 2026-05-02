#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

char *palabras[] = {"Comida", "Pomada", "Casado", "Gorila"};
char *pistas[]   = {"Se come", "Te lo pones en la piel", "Estado de matrimonio", "El mas fuerte de los monos"};

int i = 0;

// Mostrar pistas
void mostrar()
{
    printf("Pista: %s\n", pistas[i]);
}

// Cambia y despues muestra
void Palabra(int sig)
{
    i = (i + 1) % 4;
    mostrar();
    alarm(25);
}

int main()
{
    signal(SIGALRM, Palabra);

    mostrar();   // primera pista inmediata
    alarm(25);
    char intento[20];

    while(1)
    {
        printf("Adivina: ");
        scanf("%s", intento);


        int j = 0;
        int correcto = 1;

while(intento[j] != '\0' && palabras[i][j] != '\0')
{
    if(intento[j] != palabras[i][j])
    {
        correcto = 0;
        break;
    }
    j++;
}

if(intento[j] != palabras[i][j])
    correcto = 0;

if(correcto == 1)
{
    printf("Correcto\n");
}
else
{
    printf("Incorrecto\n");
}
    }

    return 0;
}