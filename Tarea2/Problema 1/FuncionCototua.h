#include <stdlib.h>
#include <stdio.h>
#define INVALID -100

typedef int tElemLista;

typedef struct nodo{ //? TDA de un nodo

    tElemLista inByte;
    tElemLista endByte;

    struct nodo *sig; //* Este es un puntero a un elemento tipo tNodo, pero omo aunn no le damos ese nombre, tenemos que llamarlo por struct nodo, que es el nombre real
}tNodo;

typedef struct //? TDA de una lista enlazada
{
    tNodo *head; //* Apunta al primer elemento de la lista
    tNodo *tail; //* Apunta al ultimo elemento de la lista
    tNodo *curr; //* Apunta al nodo actual en el que estamos en la lista
    int listSize; //* tamaño de la lista
    int pos; //* Indice del curr dentro de la lista (util por ejemplo para el getpos)
} tLinkedList;

void initList(tLinkedList *L)//? Inicializa una lista enlazada vacia 
{
    //* Se asigna el espacio necesario para que podamos incluir un puntero de tipo tNodo, en cada uno de los elementos del struct
    L->head = L->tail = L->curr = (tNodo*)malloc(sizeof(tNodo));     
    L->listSize = L->pos = 0; //* Ambos se inicializan en 0 porque no tiene elementos aun, y si es que fueramos a agregar algo, se agregaria en la posicion 0
} 

void clear(tLinkedList *L) //? Vacia una lista, dejandola inicializada, pero vacia
{
    tNodo *next;
    L->curr = L->head;
    while (L->curr != NULL)
    {
    next = L->curr->sig; //* Aqui decimos que el puntero tipo tNodo next almacenara el siguiente elemento de la lista, al que estamos revisando en este momento
    free(L->curr);
    L->curr = next;
    }
    L->head = L->tail = L->curr = (tNodo *)malloc(sizeof(tNodo));
    L->listSize = 0;
    L->pos = 0;
}

int insert(tLinkedList *L, tElemLista in, tElemLista end) //? inserta un elemento en la poscion actual, y retorna la poscion en la que el elemento quedo
{
    tNodo *aux = L->curr->sig;
    L->curr->sig = (tNodo *)malloc(sizeof(tNodo)); //* En caso de crear un nuevo nodo en la lisa, hay que asignarle memoria suficiente para guardar la cantidad de datos que se le dara
    L->curr->sig->inByte = in;
    L->curr->sig->endByte = end;
    L->curr->sig->sig = aux;
    if (L->curr == L->tail)
        L->tail = L->curr->sig;
    L->listSize++;
    return L->pos;
}

int erase(tLinkedList *L) //? Elimina el elemento que esta en la posicion actual
{
    tNodo *aux; //* Puntero a nodo, auxiliar
    aux=L->curr->sig; //*
    L->curr->sig = L->curr->sig->sig;
    free(aux);//* Queremos liberar la memoria de aquello a lo que apunta aux
    L->listSize--;
    return 0; //* Retorna 0 si es que la eliminacion fue exitosa
}//? Elimina el elemento que esta en la posicion actual

int ListSize(tLinkedList *L)
{
    return L->listSize;
}


void deleteList(tLinkedList *L) //? Elimina todos los elementos de la lista, borrando incluso la inicializacion de la lista
{
    tNodo *next;
    L->curr = L->head;
    while (L->curr != NULL)
    {
        next = L->curr->sig;
        free(L->curr);
        L->curr = next;
    }
}

void moveToStart(tLinkedList *L)//? Mueve el cursor de la lista al primer elemento (Hace que el curr que en la primera posicion)
{
    L->curr = L->head;
    L->pos = 0;
}

void moveToEnd(tLinkedList *L)//? Mueve el cursor de la lista al ultimo elemento (Hace que el curr que en la ultima posicion)
{
    L->curr = L->tail;
    L->pos = L->listSize;
}

void prev(tLinkedList *L) //? Mueve sel cursor al elemento anterior de la lista
{
    if (L->curr == L->head)
        return; //* Si es que estabamos en el primer elemento, no hay nada mas que hacer a si que retornamos
    tNodo *temp = L->head; //* Colocamos un cursor auxiliar, para recorrer hata la posicion buscada desde el inicio
    while (temp->sig != L->curr){
        temp = temp->sig;}
    L->curr = temp; //* Ahora que ya alcanzamos con el cursor auxiliar la poscion anterior, cambiamos el curr a la posicion del cursor auxiliar
    L->pos--;//* Al retroceder un espacio, el numero del cursor disminuye en 1
}

int next(tLinkedList *L) //? Mueve el cursor a la posicion siguiente, si es que el actual es el tail, no hace nada
{
    if (L->curr != L->tail)
    {
        L->curr = L->curr->sig;
        L->pos++;
    }
    return L->pos;
}

void moveToPos(tLinkedList *L, int posicion)//? Mueve el cursor a una posicion, mientras que esta exista en la lista
{
    //!if (posicion < 0 || posicion > L->listSize) warning
    if (posicion > L->listSize)
        return; //* Si es que se entrega una posicion negativa, o mas grande que la lista, no es valido
    
    if (posicion == L->pos){//* CAMBIO PERSONAL: Si es que es igual, retorna, ya que no hay nada que hacer
        return;}

    if (posicion > L->pos){ //* CAMBIO PERSONAL: Si es que es mayor que la posicion actual, avanza hasta llegar a la posicion
        while (posicion > L->pos)
            next(L);}

    else{//* Si es que es menor, comienza a buscar desde el principio
        int i;
        L->curr = L->head;
        L->pos = 0;
        for (i = 0; i < posicion; i++){
            next(L);
        }
    }
}

void printList(tLinkedList *L) //? Para printear una lista
{
    moveToStart(L);
    printf("[");
    int n = L->listSize;
    n--;
    for (int i = 0; i < n; i++)
    {
        printf("%d - %d, ", L->curr->inByte, L->curr->endByte);
        L->pos++;
        L->curr = L->curr->sig;
    }
    printf("%d - %d]\n ", L->curr->inByte, L->curr->endByte);
    moveToEnd(L);
}

int getInValue(tLinkedList *L, int pos){//? Esta funcion retorna el comienzo del bloque de memoria
    moveToPos(L, pos);
    return L->curr->sig->inByte;
}

int getEndValue(tLinkedList *L, int pos){//? Esta funcion retorna el fin del bloque de memoria
    moveToPos(L, pos);
    return L->curr->sig->endByte;
}

//? Esta función retorna el tamaño de un bloque en bytes dado un nodo determinado
int getTamBlock(tLinkedList *L, int pos){
    int tam;
    int fin = (int)getEndValue(L, pos);
    int inicio = (int)getInValue(L, pos);
    tam = (fin - inicio)+1;
    return tam;
}

int CambiarFinal(tLinkedList *L, tElemLista valorFinal ){
    L->curr->sig->endByte = valorFinal;
    return 0; //retorna 0 si es que el cambio fue exitoso
}

int CambiarInicio(tLinkedList *L, tElemLista valorInicial){
    L->curr->sig->inByte = valorInicial;
    return 0; // Retorna 0 si es que el cambio fue exitoso
}

int getPosCurr(tLinkedList *L){
    return L->pos;
}

int getPos(tLinkedList *L, tElemLista inbyte)
{
    moveToStart(L);
    int size = ListSize(L);
    while (L->pos != size){
        if (L->curr->sig->inByte == inbyte){
            return L->pos;
        }
        else{
            next(L);
        }
    }
    return INVALID;
}

tElemLista buscar_nodo_erase(tLinkedList *L, tElemLista in){

    moveToStart(L);
    int size = L->listSize;
    for (int i = 0; i < size ; i++)
    {
        if (L->curr->sig->inByte == in) {
            tElemLista B = getEndValue(L, i);
            erase(L);
            return B;
        }
        else
            next(L);
    }
    return INVALID;
}

int bytes_asignados(tLinkedList *L){
    moveToStart(L);
     int size = L->listSize;
     int contador = 0;
    for (int i = 0; i < size ; i++)
    {
        int end = (int)L->curr->sig->endByte;
        int in = ((int)L->curr->sig->inByte)-1; //Al byte inicial se le resta 1 para que, al hacer la resta, se considere dicho byte, obteniendo por ejemplo [1][2][3][4]; (4-(1-1)) = (4-0) bytes
        contador += (end-in);
        next(L);

    }
    return contador;
}

//Esta función toma un elemento de inicio y de final de un nodo, y busca en una lista L la posición correcta de inserción.
//La posición de inserción correcta es donde el inByte de el nodo actual sea menor que in2 y el inByte del siguiente del actual sea mayor que in2.
void buscar_pos_insert(tLinkedList *L, tElemLista in2, tElemLista end2){ 
//in2 es el inicio del nodo que queremos insertar en L1
//end2 es el final del nodo que queremos inserterar en L1
    moveToStart(L);
    int size = ListSize(L);

    //Iteramos en la lista mientras que la posición no sea igual al size, pues pos = {0,1,2...} y size = {1,2,3...} con pos = (size-1)
    while( L->pos < size){
        //?CASO COLA
        if (L->curr->sig == L->tail){ 
            //Tenemos que revisar 4 casos, debido a que la lista puede tener 1 elemento y ese unico elemento sería tail
            //*CASOS DE FUSIÓN CON EL NODO TAIL
            //Si el nodo actual es consecutivo con el in2:
            if (L->curr->sig->endByte == (in2 - 1) ){ //Caso de fusión del nodo a insertar con el tail, a la derecha
                CambiarFinal(L, end2);
                return;
            }
            //Si el nodo actual es consecutivo con el end2:
            else if (L->curr->sig->inByte == (end2 + 1) ){//Caso de fusión del nodo a insertar con el tail, a la izquierda
                CambiarInicio(L, in2);
                return;
            }
            //*-----------------------------------------------------

            //*CASOS DE INSERCIÓN 
            else{
                if (in2 > L->curr->sig->endByte){ //*Caso de inserción a la derecha del tail
                    next(L);
                    insert(L, in2, end2);
                    return;
                }
                if (L->curr->sig->inByte > end2){ //*Caso de inserción a la izquierda del tail
                    insert(L, in2, end2);
                    return;
                }
            }
            //*-----------------------------------------------------    
        }
        
        //*CASO INTERMEDIO 
        if((in2 > L->curr->sig->endByte) && (end2 < L->curr->sig->sig->inByte)){
            //Si no esta ni al inicio, ni al final, hay que encontrar entre que nodos está

            //*FUSÓN 3 NODOS (ANTERIOR, ACTUAL A INSERTAR, SIGUIENTE)
            if((L->curr->sig->endByte == (in2 - 1)) && (L->curr->sig->sig->inByte == (end2 + 1))){
                CambiarFinal(L, L->curr->sig->sig->endByte);
                next(L);
                erase(L);
                return;
            }
            //*-----------------------------------------------------

            //*FUSIÓN NODO CON ANTERIOR
            else if(L->curr->sig->endByte == (in2 - 1)){
                CambiarFinal(L, end2);
                return;
            }
            //*-----------------------------------------------------
 
            //*FUSIÓN CON NODO SIGUIENTE
            else if(L->curr->sig->sig->inByte == (end2 + 1)){
                next(L);
                CambiarInicio(L, in2);
                return;
            }
            //*-----------------------------------------------------

            //*INSERCIÓN EN POSICIÓN INTERMEDIA
            else{
                insert(L, in2, end2);
                return;
            }
        }

        //*CASO INICIO
        if (L->curr->sig->inByte > end2){
            if(L->curr->sig->inByte == (end2 + 1) ){ //*Si es que el inByte del primer elemento, es sucesor del end2 que queremos insertar
                CambiarInicio(L, in2);
                return;
            }
            else { //* Si no es consecutivo, simplemente se hace una insercion, quedando al inicio
                insert(L, in2, end2);
                return;
            }
        }
    next(L);
    }
}
