#include <stdio.h>
#include "linked_list.h"

//TODO: ~(1) Comprobar errores de apertura de archivos.
//TODO: ~(2) Limpiar la entrada, antes de escribir archivos binarios, con fflush()
//TODO: ~(3) Hacer rewind del archivo antes de leerlo, para asegurarnos de que comienza desde el principio
//TODO: ~(4) Cerrar los archivos al final!!
//TODO: ~(5) Liberar toda la memoria (usar ctrl f para asegurarnos que hay frees por cada malloc)
//TODO: ~(6) Compilar con -W -Wall desde terminal

int FirstFit(tLinkedList* L, int tam){
    int size = L->listSize;
    int i;
    for (i=0 ; i < size ; i++)
    {
        int block = getTamBlock(L, i);
        if (tam < block){
        return i;
        }        
    }
    return -10;
}


int main(){
    FILE *input = fopen("input1.dat", "r");  // Apertura de archivo binario input.dat, en modo lectura y escritura
    if (input== NULL) //comprobacion de apertura exitosa del archivo
    {
        printf("Problema de apertura de archivo input1.dat, finalizacion anticipada del programa");
        return 1;}

    FILE *output = fopen("output1.dat","w" );
    if (output == NULL) //comprobacion de apertura exitosa del archivo
    {
        printf("Problema de apertura de archivo para output, finalizacion anticipada del programa");
        return 2;
    }

    rewind(input); //Hacemos rewind para asegurarnos de que el cursor esta al inicio del archivo
    int M, N;
    //!fread(&M, sizeof(int), 1, input);
    // M total de memoria inicial disponible en un solo bloque contiguo
    fscanf(input, "%d", M);
    //!fread(&N, sizeof(int), 1, input); 
    // N cantidad de operaciones de petición o liberación de memoria a realizar
    fscanf(input, "%d", N);

    //Se crea una variable L1: lista de bloques disponibles
    tLinkedList* L1;
    //Se crea variable L2: Lista de bloques asignados
    tLinkedList* L2;
    //Se inicializa la lista vecía usando el TDA
    initList(L1);
    //Se inicializa la lista L2 vacía usando el TDA
    initList(L2);
    //La lista L1 se inicia con un nodo que indica un bloque de memoria contigua desde el byte 1 hasta M
    insert(L1, 1, M);
    
    char id; //caracter identificador; puede tomar los valores m (de malloc) o f (de free)
    int tamblock;
    int bytefree;
    for (int i = 0; i < N; i++) //Se itera hasta completar N lecturas (correspondiente a N opercaciones)
    {
        //Se lee el primer caracter de cada línea
        fread(&id, sizeof(char), 1, input);
        //Si id es m sabemos que la operación será un malloc, por lo que a la m le proceden 5 caracteres antes del int
        if (id == "m")
        {
            fseek(input, 6, SEEK_CUR); //?Agregamos el espacio como un caracter contable
            //fread(&tamblock, sizeof(int),1,input);
            fscanf(input, "%d", tamblock); //* Aqui leemos cuanta memoria tenemos que asignar

            int NodoLibre = FirstFit(L1, tamblock); // Encontramos el primer bloque de memoria que cumple con el espacio suficiente para allocar la memoria solicitada
            if (NodoLibre = -10){ // Este caso sucede si es que no hay ningun bloquye de memoria con el espacio solicitado
                fprintf(output, "%s %d %s", "Bloque de ", tamblock, "bytes NO puede ser asignado\n"); 
            }
            else if{
                moveToPos(L1, NodoLibre); // Nos movemos al bloque de memoria que puede allocar lo solicitado
                getEndValue(L1); // Con esto, quitamos de este bloque de memoria, el espacio necesario para tamblock, NOTA: puede tambien quitarse desde el inicio

            }
        }
        //Si id es f sabemos que la operación será un free, por lo que a la f le proceden 3 caracteres antes del int
        else if (id == "f")
        {
            fseek(input, 4, SEEK_CUR); //?Agregamos el espacio como un caracter contable
            fscanf(input, "%d" , bytefree);
        }
        
    }
    






    return 0;
}