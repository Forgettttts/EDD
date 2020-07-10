#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int main(){
    FILE *input = fopen("input1.dat.txt", "r"); // Apertura de archivo binario input.dat, en modo lectura y escritura
    if (input == NULL)                          //comprobacion de apertura exitosa del archivo
    {
        printf("Problema de apertura de archivo input1.dat, finalizacion anticipada del programa");
        return 1;
    }

    rewind(input); //Hacemos rewind para asegurarnos de que el cursor esta al inicio del archivo
    int M, N;
    // M: total de memoria inicial disponible en un solo bloque contiguo
    fscanf(input, "%d", &M);
    // N: cantidad de operaciones de petición o liberación de memoria a realizar
    fscanf(input, "%d", &N);

    char *id = (char *)malloc(sizeof(char) * 8);
    fscanf(input, "%s", id);
    printf("%s", id);

    fclose(input);
    return 0;
}