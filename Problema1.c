/*PROBLEMA 1: comienzo
 
~Funcion:
    //TODO char∗∗ buscar_str(char ∗∗ S, int n, char ∗ P) 
 
    Se nos entregaran 3 parametros:
        -char** S= //*Un puntero, que apunta a un puntero, el cual apunta a un char. Ya que este es un puntero de puntero, cuando llamemos a la funcion
                   //* tendremos que entregarla la direccion de memoria del puntero
        -int n= //*Cantidad de strings que contiene el arreglo S
        -char* P= //*Un string
    De donde nuestro programa debe encontrar cuantos strings pertenecientes a S, contienen al string P.
    //TODO: La funcion debe retornar un arre glo  con todos los strings que cumplan con la condicion buscada
 
~Main:
    //! Entrada:
 
    Leer dos archivos: S.txt y P.txt:
 
    S.txt : //?Almacena los strings correspondientes a S, uno por linea, el largo maximo de cada linea es 200 [char]
    P.txt : //?Almacena los strings que se buscaran en S, por lo que por cada string de P, habra que invocar
//?            la funcion buscar_str()
    //! Salida:
 
    Por cada string de P, se debe:
    //TODO: Generar un archivo con el nombre del string con la extension .out
    //TODO: Dentro de cada archivo, cada linea es un 1 string que cumple con la condicion de buscar_str()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **buscar_str(char **S, int n, char* P, int* m){
    char** Ret= (char**)malloc(sizeof(char*)*n);// Asignamos memoria para el arreglo de string que se retornara
    int tamRet = 0; // tamRet= largo del arreglo de strings Ret, al comienzo es 0
    int largo_P;
    largo_P=strlen(P);
    int i=0; //contador para ver el string S
    for(i=0;i<n;i++){  //iremos viendo string por string de S
        int y, igual=0; //igual es un flag que nos dice que si es =0, p es prefijo de S[i], y si es =1 P no es prefijo de S[i]
        for (y=0; y<largo_P;y++){ //iremos viendo letra por letra tanto de P como se S[i]
            if (P[y]=='\n' || ((P[y])!=(S[i][y]))){
                igual=1;
                break;
            }
            
            }
        if (igual==0){
            Ret[tamRet]= S[i]; //Ret[tamRet]=S[i];
                tamRet++;
        }
        
    }
    *m=tamRet; //le damos a m el valor de tamRet
    return Ret;
    free(Ret);
}

int main()
{
    //! Abriremos el archivo correspondiente a S
    FILE *diccionario;                //Aqui abriremos el archivo que tiene todas las palabras, el que revisaremos
    diccionario = fopen("S.txt","r"); //diccionario es una variable de tipo puntero que trabaja con el archivo que contiene palabras
    if (diccionario == NULL)
    {
        printf("Error al abrir el archivo S, fin anticipado del programa"); // Se asume que el archivo S.txt y el archivo P.txt nunca cambian de nombre
        return 1;
    }
    //? Aqui ya esta abierto el archivo 's', y también revisamos si es que se abrió mal
    //? Contaremos las lineas de S para saber cuántos elementos tendrá el array con los strings de s
    int nlineas=0;
    char caracter;
    while (caracter = fgetc(diccionario))
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
    rewind(diccionario);
    //?Aquí ya sabemos cuantas lineas tiene S, y por ende sabemos cuantas palabras hay en S
    //! Aqui ya tenemos el valor de 'n' = nlineas en la función buscar_str()

    //? Ahora le definiremos un array y le daremos memoria dinamica para que guarde la cantidad de datos que necesitemos, sabiendo la cantidad de datos y el largo maximo de cada string
    char** palabras= (char**)malloc(sizeof(char*)*1000000); // espacio para 1000000 de palabras
    for (int i = 0; i <= nlineas; i++)
    {
        palabras[i] = (char *)malloc(201 * sizeof(char));// a cada espacio dentro de palabras[] se le asigna memoria dinamica
        fscanf(diccionario, "%s", palabras[i]); // cada string de el archivo se guarda en palabras[]
    }
    //?Aqui ya deberían estar todas las palabras agregadas al array palabras

    fclose(diccionario); //*Cerramos el archivo, porque ya sacamos toda la info que necesitábamos

    //!Ahora abriremos el archivo correspondiente a P
    FILE *prefijos;
    prefijos = fopen("P.txt", "r");
    if (prefijos == NULL)
    {
        printf("Error al abrir el archivo P, fin anticipado del programa");
        return 2;
    }
    //? Ya está abierto el archivo P, almacenado en la variable prefijos
    //? Aqui contamos la cantidad de lineas en el archivo p (cantidad de prefijos)
    int nprefijos = 0;
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
    rewind(prefijos);
    //? Aqui ya tenemos la cantidad de prefijos, guardados en la variable nprefijos
    //? Ahora crearemos un array de strings, con la capacidad suficiente como para poder guardar los prefijos, y los guardamos
    char **lista_prefijos=(char **) malloc(sizeof(char *) * 1000); // espacio para 1000 prefijos
    for (int k = 0; k <= nprefijos; ++k)
    {
        lista_prefijos[k] = (char *)malloc(201 * sizeof(char)); // espacio para cada prefijo
        fscanf(prefijos, "%s", lista_prefijos[k]);
    }
    
    //?Aqui ya deberian de estar todos los strings de P en el arreglo lista_prefijos

    //? Cerramos el archivo, ya que tenemos toda la info que necesitamos
    fclose(prefijos);
    //?Archivos cerrados

    //?Ahora procedemos a crear los archivos de respuesta
    //? Declaramos un ciclo for para poder aplicar la funcion en cada string de P
    for (int g=0; g <nprefijos; g++) {
        int m;
        //? Asignamos memoria dinamica a una variable RESPUEsta que es donde se guardaran los strings de S que cumplan con tneer como prefijo a P[g]
        char** RESPUESTA= (char**)malloc(sizeof(char*)*nlineas); 
        RESPUESTA=buscar_str(palabras, nlineas, lista_prefijos[g],&m ); // Aplicamos funcion a el string P[g]
        //? Ciclo for para poder escribir
        
        char titulo[205]; //definimos este arreglo con el tamaño maximo que pudiera llegar a tener el titulo
        strcpy(titulo, lista_prefijos[g]);//copiamos en el titulo, el nombre del prefijo actual
        strcat(titulo, ".out"); //añadimos la extension .out al titulo del archivo
        // titulo es el nombre de el archivo, lo que es equivalaente al nombre del prefijo que estamos analizanod as la extension .out
        FILE *answer;
        answer = fopen(titulo, "w");
        for (int t=0; t < m; t++){
            fprintf(answer, "%s\n", RESPUESTA[t]);
        }
        fclose(answer);   
        }
    free(lista_prefijos); //Tenemos que liberar la memoria dinámica solicitada
    free(palabras);       //Tenemos que liberar la memoria dinámica solicitada
    return 0;
}
