#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv)
{
    FILE *transacciones = fopen("transacciones.txt", "r");
    if (transacciones == NULL) //revisamos si es que el archivo se abrio bien
    {
        printf("Error al abrir el archivo de las transacciones, fin anticipado del programa");
        return 1;
    }
    char caracter;
    fscanf(transacciones, "%c\n", &caracter);
    printf("el caracter es: %c\n", caracter);
    if (caracter == '+')
    {
        printf("Es con simple\n");
    }


    return 0;
}