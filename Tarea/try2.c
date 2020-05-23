
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char prefijo[8]="flor";
    char* gato[8] = strcpy(gato, prefijo);
    char* perro=strcat(prefijo, "sol");
    printf("gato=%s\n", gato);
        /*
    for(int i=0; i<4;i++ ){
        printf("%s", perro[i]);
    }*/

        /* FILE *diccionario;
    diccionario = fopen("S.txt", "r");
    if (diccionario == NULL)
    {
        printf("Error al abrir el archivo S, fin anticipado del programa");
        return 1;
    }

    int nlineas=0;
    char caracter;

    while ((caracter = fgetc(diccionario)))
    { //********* fuente de optimización
        if (caracter == '\n')
        {
            nlineas++;
        }
        if (caracter == EOF)
        {
            nlineas++;
            break;
        }
    }

    char *palabras[nlineas];
    for (int i = 0; i <= nlineas; ++i)
    {
        palabras[i] = (char *)malloc(200 * sizeof(char));
        fgets(palabras[i], 201, diccionario);
    }

    fclose(diccionario);

    printf("flag3\n");
    
    FILE *prefijos;
    prefijos = fopen("P.txt", "r");
    if (prefijos == NULL)
    {
        printf("Error al abrir el archivo P, fin anticipado del programa");
        return 2;
    }

    int nprefijos=0;
    char letra;
    while ((letra = fgetc(prefijos)))
    { //********* fuente de optimización
        if (letra == '\n')
        {
            nprefijos++;
        }
        if (letra == EOF)
        {
            nprefijos++;
            break;
        }
    }

    char *lista_prefijos[nprefijos];
    for (int k = 0; k <= nprefijos; ++k)
    {
        lista_prefijos[k] = (char *)malloc(200 * sizeof(char));
        fgets(lista_prefijos[k], 201, prefijos);
    }

    fclose(prefijos);
    printf("%d\n", nprefijos);
    printf("flag1\n");
    int e,r;
    for (e=0; e<nlineas; e++){
        printf("%s\n", palabras[e]);
    }
    for (r=0; r<nprefijos; r++)
    {
        printf("%s\n", palabras[r]);
    }

    free(lista_prefijos);
    free(palabras);
    LO DE ARRIBA NO LO LIBERAMOS PORQUE SE PERDERÍAN LOS STRINGS DE PALABRAS Y PREFIJOS...*/
        return 0;
}