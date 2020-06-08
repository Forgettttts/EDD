#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**** Detalles de la función:
 * Nombre: buscar_str
 * *******
 * Resumen:
    * La función buscar_str, compara un prefijo P con cada palabra del arreglo S de tamaño n,
    * esta comparación la hace iterando sobre los caracteres del prefijo P. Si uno de estos caracteres
    * no coincide con los primeros caracteres de alguna palabra en S, dicha palabra se descarta, y aquellas
    * que sí coincidan con todos los caracteres del prefijo se guardan en un arreglo Ret.
 * *******
 * Input:
    * char** S : Es un arreglo que contiene arreglos de caracteres; strings.
 *Corresponden a las palabras a comparar con el prefijo P
    * int n: Es un entero. dicho entero es el tamaño de S, es decir, la cantidad de palabras.
    * char* P :  Es un arreglo de caracteres, es decir un string, que respresenta el prefijo.
    * int* m : Es un puntero que apunta a la dirección de memoria de un entero, el cual representará 
 *el tamaño del arreglo Ret que retorna esta función.
 * Return:
    *  char** Ret : es un arreglo que contiene las palabras  que contienen al prefijo P
 * ****/

char **buscar_str(char **S, int n, char* P, int* m){
    char** Ret = (char**)malloc(sizeof(char*)*n);    // Asignamos memoria para el arreglo de strings que se retornará.
    int tamRet = 0;   // tamRet= largo del arreglo de strings Ret, al comienzo es 0
    int largo_P;
    largo_P = strlen(P);
    
    for(int i=0; i<n; i++){    //Iteramos sobre cada palabra que contiene S
        int igual = 0;    //igual es un flag que nos dice que si es =0, p es prefijo de S[i], y si es =1 P no es prefijo de S[i]
        for (int y=0; y<largo_P; y++){    //Iteramos sobre los caracteres, tanto de P como de S[i]
            if (P[y]=='\n' || ((P[y])!=(S[i][y]))){
                igual=1;
                break;
            }
            
            }
        if (igual==0){
            Ret[tamRet]= S[i]; 
                tamRet++;
        }
        
    }
    *m=tamRet;   //m ahora tiene el valor del tamaño de Ret
    realloc(Ret, sizeof(char*) * tamRet);  
    return Ret;
    free(Ret);
}

int main()
{
    
    FILE *diccionario;  // diccionario es una variable de tipo puntero que trabaja con el archivo que contiene palabras
    diccionario = fopen("S.txt","r");    // Se asume que el archivo S.txt y el archivo P.txt nunca cambian de nombre
    if (diccionario == NULL)
    {
        printf("Error al abrir el archivo S, fin anticipado del programa"); 
        return 1;
    }
    

// Contaremos las lineas del archivo S.txt para saber cuántos elementos tendrá el array con los strings de S
    int nlineas=0;
    char caracter;
    while (caracter = fgetc(diccionario)){ 
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
    rewind(diccionario);
    

    // Ahora definiremos un array y le asignaremos memoria dinamica para que guarde la cantidad de palabras que ya sabemos (largo nlineas)
    char** palabras= (char**)malloc(sizeof(char*)*1000000); 
    for (int i = 0; i <= nlineas; i++)
    {
        palabras[i] = (char *)malloc(201 * sizeof(char));   // A cada palabra (palabras[i]) dentro del arreglo palabras se le asigna memoria dinamica
        fscanf(diccionario, "%s", palabras[i]);   // Cada string de el archivo se guarda en palabras[]
    }
    

    fclose(diccionario);

    
    FILE *prefijos; // prefijos: Puntero a archivo de prefijos
    prefijos = fopen("P.txt", "r");
    if (prefijos == NULL)
    {
        printf("Error al abrir el archivo P, fin anticipado del programa");
        return 2;
    }
    
    // Contaremos la cantidad de lineas en el archivo prefijos 

    int nprefijos = 0;   // nprefijos: cantidad de prefijos
    char letra;
    while ((letra = fgetc(prefijos)))
    { 
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
    rewind(prefijos);
    

    // Crearemos un array de strings, con la memoria suficiente para guardar los prefijos, y los guardamos en dicho arreglo.
    char **lista_prefijos=(char **) malloc(sizeof(char *) * 1000); 
    for (int k = 0; k <= nprefijos; ++k)
    {
        lista_prefijos[k] = (char *)malloc(201 * sizeof(char));    // Se asigna espacio en memoria para cada prefijo
        fscanf(prefijos, "%s", lista_prefijos[k]);    // Se guarda cada prefijo en el arreglo lista_prefijos
    }
    

    fclose(prefijos);
    
    
    // Declaramos un ciclo for para poder aplicar la funcion buscar_str en cada string de P
    for (int g=0; g <nprefijos; g++) {
        int m;

        // Invocamos la función buscar_str para cada prefijo P = lista_prefijos[g]  
        char** RESPUESTA=buscar_str(palabras, nlineas, lista_prefijos[g],&m ); 
        
        int tamtitulo= strlen(lista_prefijos[g])+5;
        char titulo[tamtitulo];                   

        // Copiamos en el titulo, el nombre del prefijo actual
        strcpy(titulo, lista_prefijos[g]);

        // Añadimos la extension .out al titulo del archivo
        strcat(titulo, ".out");    
               
        FILE *answer;                                            
        answer = fopen(titulo, "w");
        for (int t=0; t < m; t++){
            fprintf(answer, "%s\n", RESPUESTA[t]);
        }
        fclose(answer);
    }

    // Procedemos a liberar memoria
    
    for (int f = 0; f <= nlineas; f++)
    {
        free(palabras[f]); 
    }

    for (int j = 0; j <= nlineas; j++)
    {
        free(lista_prefijos[j]); 
    }

    free(lista_prefijos); 
    free(palabras);  

    return 0;
}
