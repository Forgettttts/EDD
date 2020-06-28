#include <stdlib.h>
#include <stdio.h>

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
    unsigned int listSize; //* tamaño de la lista
    unsigned int pos; //* Indice del curr dentro de la lista (util por ejemplo para el getpos)
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

void moveToPos(tLinkedList *L, unsigned int posicion)//? Mueve el cursor a una posicion, mientras que esta exista en la lista
{
    if (posicion < 0 || posicion > L->listSize)
        return; //* Si es que se entrega una posicion negativa, o mas grande que la lista, no es valido
    
    if (posicion == L->pos){//* CAMBIO PERSONAL: Si es que es igual, retorna, ya que no hay nada que hacer
        return;}

    if (posicion > L->pos){ //* CAMBIO PERSONAL: Si es que es mayor que la posicion actual, avanza hasta llegar a la posicion
        while (posicion > L->pos)
            next(L);}

    else{//* Si es que es menor, comienza a buscar desde el principio
        unsigned int i;
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

int getInValue(tLinkedList *L, unsigned int pos){//? Esta funcion retorna el comienzo del bloque de memoria
    moveToPos(L, pos);
    return L->curr->sig->inByte;
}

int getEndValue(tLinkedList *L, unsigned int pos){//? Esta funcion retorna el fin del bloque de memoria
    moveToPos(L, pos);
    return L->curr->sig->endByte;
}

//? Esta función retorna el tamaño de un bloque en bytes dado un nodo determinado
int getTamBlock(tLinkedList *L, unsigned int pos){
    return getEndValue(L, pos) - getInValue(L, pos);
}

int CambiarFinal(tLinkedList *L, unsigned int valorFinal ){
    L->curr->endByte=valorFinal;
    return 0; //retorna 0 si es que el cambio fue exitoso
}

int CambiarInicio(tLinkedList *L, unsigned int valorInicial){
    L->curr->sig->inByte=valorInicial;
    return 0; // Retorna 0 si es que el cambio fue exitoso
}

int getPosCurr(tLinkedList *L){
    return L->pos;
}

int getPos(tLinkedList *L, int inbyte)
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
    return -10;
}

void buscar_pos_insert(tLinkedList *L, int inbyte, int endbyte){ //!en el programa del problemas vamos a tener que obtener el valor de término mediante getEndValue y chantárselo a esta fun como parametro :D

    moveToStart(L);
    int size = ListSize(L);
    while ( L->pos != size){ //* Los casos que pueden salir es de insercion al inicio o dentro
        while (L->curr->sig->inByte < inbyte){//* Si es que el elemento de la izquierda es menor que el elemento que queremos insertar
            if (L->curr->sig->sig->inByte > inbyte){ //* Si es que el elemento sigueinte al actual, es mayor al que queremos insertar
                if(L->curr->sig->endByte == (inbyte - 1)){ //* Si es que el final (endByte) del nodo actual en L1, es antecesor del inbyte del nodo a insertar, se fusionan
                    if (L->curr->sig->sig->inByte == (endbyte + 1)){ //* Si es que el final del nodo a insertar (endbyte), es antecesor del inByte del siguiente nodo (inByte) se fusionan
                        L->curr->sig->sig->inByte = L->curr->sig->inByte; //! Entró a los 2 if anteriores, se fusionan los 3 nodos
                        erase(L);
                        return; //* Retornamos pq no hay nada mas que hacer
                    }
                    else{ //!entró al primer if pero no al segundo, por lo que se fusionan los dos primeros nodos, simplemente se cambia el fin del nodo existente por el fin del nodo que se insertaría
                        CambiarFinal(L, endbyte);
                        return; //* Retornamos pq no hay nada mas que hacer
                    }
                }
                else{ //* Si es que no es consecutivo con el actual, entra aqui, pq es un else
                    if (L->curr->sig->sig->inByte == (endbyte + 1)){//! El final del nodo a insertar (endbyte) se fusiona con el nodo siguiente en L1
                        next(L);
                        CambiarInicio(L, inbyte); //!Se fusionan sólo el nodo a insertar y el siguiente del actual en L1
                        return; //* Retornamos pq no hay nada mas que hacer
                    }
                    else{
                        insert(L, inbyte, endbyte);
                        return;
                    } 
                }
            }
            else {
                next(L);//* Este next es por si no pertenece entre 2 nodos, para avanzar al siguiente
            }
            
        }       
        //* Si es que no entro al while anterior, es pq es un caso de insercion al inicio

        if (L->curr->sig->inByte == (endbyte + 1)){//* Esto significa que el elemento a insertar es antecesor directo del primer elemento
            CambiarInicio(L, inbyte); //!Se fusionan sólo el nodo a insertar y el siguiente del actual en L1
            return; //* Retornamos pq no hay nada mas que hacer
        }

        //!!HASTA AQUÍ LLEGAMOSSSSS!!! falta caso de inserción al final (cambiar el tail y ver caso de fusión)
        else{
                next(L);
        }
        
        else
        { //*Este caso es por si es que la insercion debe realizarse en el inicio
            return;
        }
    }
    return;//* En este caso, el curr quedo en el tail, por lo que no entro en el while, esto significa que la insercion del elemento se hara al fina, actualizando el tail
    
}







