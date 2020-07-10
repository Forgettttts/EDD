#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("Problema de apertura de archivo input1.dat, finalizacion anticipada del programa");
        return 1;
    }

    int u; //* u= Cantidad de operaciones a realizar
    fscanf(input, "%d", &u);
    printf("THIS IS THE u = %d\n", u);

    //TODO: Agregar al readme que el archivo tiene que contener todas las instrucciones en mayusculas

    //for (int i = 0; i < u; i++)

    while(feof(input)==0)
    {
        int elem;
        char* id = (char *)malloc(sizeof(char) * 9);
        fscanf(input, "%s", id);

        printf("THIS IS THE OPERATION= %s\n", id);

        if (strcmp(id, "INSERTAR") == 0) //* Insertar elemento en el ABB
        {
            
            printf("entra a insertar\n");
            fscanf(input, "%d", &elem);
            printf("numero= %d\n", elem);
        }
        if (strcmp(id, "BORRAR") == 0) //* Borrar el elemento del ABB
        {
            printf("entra a borrar\n");
            fscanf(input, "%d", &elem);
            printf("numero= %d\n", elem);
        }
        if (strcmp(id, "PREORDEN") == 0) //* Entregar ABB en preorden
        {
            printf("entra a preorden\n"); // la operación preorden en el TDA, ya printea por sí misma
        }
        if (strcmp(id, "SUCESOR") == 0) //* Entregar el sucesor del numero en el ABB
        {
            printf("entra a sucesor\n");
            fscanf(input, "%d", &elem);
            printf("numero= %d\n", elem);
        }
    }
    fclose(input);
    return 0;
}