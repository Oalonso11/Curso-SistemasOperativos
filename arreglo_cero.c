#include <stdio.h> 
int main(){
    int n = 10;
    int arreglo[10] = {1,12,4,7,9,5,5,2,8,0};
    int i;

    printf("Arreglo con los ceros desordenados: ");
    for (i=0; i<n ; i++){
        printf("%d ",arreglo[i]);
    }

   int cerop = 0;
   for(i=0; i<n ; i++){
    if (arreglo[i] == 0){
        int temp = arreglo[i];
        arreglo[i] = arreglo[cerop];
        arreglo[cerop] = temp;
        cerop++;
    }
   }

   printf("\nEl arreglo ordenado es: ");
   for (i=0;i<n;i++){
    printf("%d ",arreglo[i]);
   }

   printf("\nEl valor final de cerop es: %d",cerop);

    return 0;


}