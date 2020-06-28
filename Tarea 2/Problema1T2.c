#include <stdio.h>
#include "linked_list.h"

//TODO: ~(1) Comprobar errores de apertura de archivos.
//TODO: ~(2) Limpiar la entrada, antes de escribir archivos binarios, con fflush()
//TODO: ~(3) Hacer rewind del archivo antes de leerlo, para asegurarnos de que comienza desde el principio
//TODO: ~(4) Cerrar los archivos al final!!
//TODO: ~(5) Liberar toda la memoria (usar ctrl f para asegurarnos que hay frees por cada malloc)
//TODO: ~(6) Compilar con -W -Wall desde terminal


int FirstFit(tLinkedList* L, int tam){

    int size = ListSize(L);
    int i;
    for (i=0 ; i < size ; i++)
    {
        int block = getTamBlock(L, i);
        if (tam <= block){
        return i;
        
        }        
    }
    return -10;
}





int main(){

    FILE *input = fopen("input1.dat", "r");  // Apertura de archivo binario input.dat, en modo lectura y escritura
    if (input == NULL) //comprobacion de apertura exitosa del archivo
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
    // M: total de memoria inicial disponible en un solo bloque contiguo
    fscanf(input, "%d", M);
    //!fread(&N, sizeof(int), 1, input); 
    // N: cantidad de operaciones de petición o liberación de memoria a realizar
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
        //Si id es m sabemos que la operación será un malloc, por lo que a la m le proceden 6 caracteres antes del int (5 letras y 1 espacio).
        if (id == "m")
        {
            fseek(input, 6, SEEK_CUR); //?Agregamos el espacio como un caracter contable
            
            fscanf(input, "%d", tamblock); //* Aqui leemos cuanta memoria tenemos que asignar

             // Encontramos el primer bloque de memoria que cumple con el espacio suficiente para allocar la memoria solicitada
            int NodoLibre = FirstFit(L1, tamblock);
            
            if (NodoLibre = -10){ // Este caso sucede si es que no hay ningun bloque de memoria con el espacio solicitado
                fprintf(output, "%s %d %s", "Bloque de ", tamblock, "bytes NO puede ser asignado\n"); 
            }
            else {
                moveToPos(L1, NodoLibre); // Nos movemos al bloque de memoria que puede allocar lo solicitado
                
                //Se inserta en L2 el Nodo correspondiente al bloque de memoria asignado
                insert(L2, getInValue(L1, getPosCurr(L1)), (getInValue(L1, getPosCurr(L1)) + tamblock)); 

                int nuevo_in_L1 = (getInValue(L1, getPosCurr(L1)) + tamblock + 1); //* Aqui calculamos el nuevo comienzo del bloque de memoria restante luego de obtener la cantidad de memoria solicitada
                CambiarInicio(L1, nuevo_in_L1); // Quitamos de este bloque de memoria, el espacio necesario para tamblock (Re-definiendo el comienzo del bloque )
                
                fprintf(output, "%s %d %s %d", "Bloque de ", tamblock, " bytes asignado a partir del byte ",  getInValue(L2, getPosCurr(L2)));
                moveToEnd(L2); //* Luego de insertar, dejamos el current al final de L2 para que la siguiente inserción (ciclo for) se haga al final.
            }
        }
        //Si id es f sabemos que la operación será un free, por lo que a la f le proceden 4 caracteres antes del int (3 letras + 1 espacio)
        else if (id == "f")
        {
            fseek(input, 4, SEEK_CUR); //?Agregamos el espacio como un caracter contable
            fscanf(input, "%d" , bytefree); //byetfree es el byte de inico del bloque a liberar
            //!Falta una linea de codigo que nos mueva el curr de L1 a la pos en donde vamos a insertar el sig elem.
            
            
            

            //Eliminar de la lista L2
            //? moveToPos(L2, getPos(L2, bytefree)); //No sabemos si el cursor ya está en la posición del elem que queremos eliminar (se movió al hacer getPos(L2, bytefree)?)
            erase(L2); //!aQUÍ SUPONEMOS QUE EL CURR EN L2 YA ESTÁ POSICIONADO EN, AL HACER getPos(L2, bytefree) EN EL INSERT DE L1
            
        }
        
    }
    






    return 0;
}