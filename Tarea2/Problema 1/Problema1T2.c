#include <stdio.h>
#include <string.h>
#include "FuncionCototua.h"

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
    return INVALID;
}


int main(){

    FILE *input = fopen("input1.dat.txt", "r");  // Apertura de archivo binario input.dat, en modo lectura y escritura
    if (input == NULL) //comprobacion de apertura exitosa del archivo
    {
        printf("Problema de apertura de archivo input1.dat, finalizacion anticipada del programa");
        return 1;}

    FILE *output = fopen("output1.dat.txt","w" );
    if (output == NULL) //comprobacion de apertura exitosa del archivo
    {
        printf("Problema de apertura de archivo para output, finalizacion anticipada del programa");
        return 2;
    }

    rewind(input); //Hacemos rewind para asegurarnos de que el cursor esta al inicio del archivo
    int M, N;
    // M: total de memoria inicial disponible en un solo bloque contiguo
    fscanf(input, "%d", &M);
    // N: cantidad de operaciones de petición o liberación de memoria a realizar
    fscanf(input, "%d", &N);

    //Se crea una variable L1: lista de bloques disponibles
    tLinkedList L1;
    //Se crea variable L2: Lista de bloques asignados
    tLinkedList L2;
    //Se inicializa la lista vecía usando el TDA
    initList(&L1);
    //Se inicializa la lista L2 vacía usando el TDA
    initList(&L2);
    //La lista L1 se inicia con un nodo que indica un bloque de memoria contigua desde el byte 1 hasta M

    insert(&L1, 1, M);
    
    char m[]="malloc";
    char f[]="free"; //caracter identificador; puede tomar los valores m (de malloc) o f (de free)
    int tamblock;
    int bytefree;
    for (int i = 0; i < N; i++) //Se itera hasta completar N lecturas (correspondiente a N opercaciones)
    {
        char* id=(char*)malloc(sizeof(char)*8);
        
        //Se lee el primer caracter de cada línea
        fscanf(input, "%s", id);
        printf("%s %s", id,"\n");
        //Si id es m sabemos que la operación será un malloc, por lo que a la m le proceden 6 caracteres antes del int (5 letras y 1 espacio).
        if ((strcmp(id, m)==0))
        {
    
            fscanf(input, "%d", &tamblock); //* Aqui leemos cuanta memoria tenemos que asignar

             // Encontramos el primer bloque de memoria que cumple con el espacio suficiente para allocar la memoria solicitada
            int NodoLibre = FirstFit(&L1, tamblock);
            
            
            if ((NodoLibre == INVALID)){ // Este caso sucede si es que no hay ningun bloque de memoria con el espacio solicitado
                fprintf(output, "%s %d %s", "Bloque de ", tamblock, " bytes NO puede ser asignado\n"); 
            }
            else {
                moveToPos(&L1, NodoLibre); // Nos movemos al bloque de memoria que puede allocar lo solicitado
                
                //Se inserta en L2 el Nodo correspondiente al bloque de memoria asignado
                insert(&L2, getInValue(&L1, getPosCurr(&L1)), (getInValue(&L1, getPosCurr(&L1)) + tamblock-1)); 
                if (tamblock == getTamBlock(&L1 ,NodoLibre))
                {
                    erase(&L1);
                }
                else
                {
                    int nuevo_in_L1 = (getInValue(&L1, getPosCurr(&L1)) + tamblock); //* Aqui calculamos el nuevo comienzo del bloque de memoria restante luego de obtener la cantidad de memoria solicitada
                    CambiarInicio(&L1, nuevo_in_L1); // Quitamos de este bloque de memoria, el espacio necesario para tamblock (Re-definiendo el comienzo del bloque )
                }
                
                   
                fprintf(output, "%s %d %s %d %s", "Bloque de ", tamblock, " bytes asignado a partir del byte ",  getInValue(&L2, getPosCurr(&L2)), "\n");
                moveToEnd(&L2); //* Luego de insertar, dejamos el current al final de L2 para que la siguiente inserción (ciclo for) se haga al final.
                
            }
        free(id);
        }
        //Si id es f sabemos que la operación será un free, por lo que a la f le proceden 4 caracteres antes del int (3 letras + 1 espacio)
        else if ((strcmp(id,f) == 0))
        {
            printf("%s","A ESTE FLAG SÍ ENTRA\n"); //? A ESTE FLAG SÍ ENTRA
            fscanf(input, "%d" , &bytefree); //byetfree es el byte de inico del bloque a liberar
            tElemLista ByteFree = (tElemLista)bytefree;
            tElemLista endfree = buscar_nodo_erase(&L2, ByteFree); // Eliminamos de la lista L2, el nodo que empezaba con el byte ByteFree
            buscar_pos_insert(&L1, ByteFree, endfree);
            int liberados = (int)endfree - bytefree;
            liberados++; //agregamos 1 para que cuente la cantidad de bytes totales
            fprintf(output, "%s %d %s", "Bloque de ", liberados, " bytes liberado\n");
            free(id);
        } 
    }
    fclose(input);
    int BSA = ListSize(&L2); //Cantidad de Bloques Sin Asignar
    int asignados = bytes_asignados(&L2);
    fprintf(output, "%s %d %s %d %s", "Quedaron ", BSA, " bloques sin liberar  (", asignados, " bytes)\n");
    fclose(output); 
    return 0;
}