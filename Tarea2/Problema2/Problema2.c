#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDA_ABB_ULTIMO.h"

int main()
{
    FILE *input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("Problema de apertura de archivo input1.dat, finalizacion anticipada del programa");
        return 1;
    }

    tABB TREE;       //*Creamos el abrol binario
    initTree(&TREE); //*Se inicializa el arbol

    int u; //* u= Cantidad de operaciones a realizar
    fscanf(input, "%d", &u);
    printf("THIS IS THE u = %d\n", u);

    //TODO: Agregar al readme que el archivo tiene que contener todas las instrucciones en mayusculas

    //for (int i = 0; i < u; i++)

    while (feof(input) == 0)
    {
        int elem;
        char *id = (char *)malloc(sizeof(char) * 9);
        fscanf(input, "%s", id);

        if (strcmp(id, "INSERTAR") == 0) //* Insertar elemento en el ABB
        {
            fscanf(input, "%d", &elem);
            printf("Entra a insertar, el numero %d\n", elem);
            insert(&TREE, elem);
            printf("termina isnercion\n\n");
        }
        if (strcmp(id, "BORRAR") == 0) //* Borrar el elemento del ABB
        {
            printf("Comeinza borrado\n");
            fscanf(input, "%d", &elem);
            printf("entra a borrar el elemento %d\n", elem);
            treeNode* Ubicacion= find(&TREE, elem);
            borrar(&TREE, Ubicacion);
            printf("Termina borrado\n\n");
        }
        if (strcmp(id, "PREORDEN") == 0) //* Entregar ABB en preorden
        {
            printf("entra a preorden\n");
            preOrden(&TREE); // la operación preorden en el TDA, ya printea por sí misma
            printf("Preorden lsito\n\n");
        }
        if (strcmp(id, "SUCESOR") == 0) //* Entregar el sucesor del numero en el ABB
        {
            printf("entra a sucesor\n");
            fscanf(input, "%d", &elem);
            printf("Sucesor de %d: \n", elem);
            sucesor(&TREE, (tipoElem)elem, u);
            printf("%d\n", getValue(sucesor(&TREE, (tipoElem)elem, u)));
            printf("termjina sucesor\n\n");
        }
        free(id);
    }
    fclose(input);
    return 0;
}