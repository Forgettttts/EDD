#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char* solcio="flor";
    char* nuevo;
    strcpy(nuevo, solcio);
    strcat(nuevo, ".txt");
    printf("Nuevo = %s\n", nuevo);
    FILE *fp;
    fp=fopen(nuevo, "r");

    if (fp == NULL){
        printf("Error al abrir el archivo\n");
    }

    char sol[1000];
    fscanf(fp, "%[^\n]", sol);
    printf("%s\n", sol);

    fclose(fp);
    return 0;
}