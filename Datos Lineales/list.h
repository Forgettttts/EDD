#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000000
#define invalid_element -12345

#include <stdio.h>
#include <stdlib.h>

typedef int tElemLista; //? es un entero, si no me equivoco, es algun elemento dentro de la lista que estamos trabajando
typedef struct//? Struct de una lista
{
    unsigned int maxSize;  //? Tamaño amximo de la lista
    unsigned int listSize; //? Tamaño actual de la lista
    unsigned int curr;     //? Posicion actual del cursor dentro de la lista (siguiente al ultimo elemento)
    tElemLista *listArray; //?  DIRECCION DE MEMORIA, puntero al elemento en la posicion curr del arreglo listArray de tamaño actual listSize, este es olo un puntero, recien le diremos a que va a apuntar, cuando inicializemos la lista
} tLista;

void initList(tLista *L){ //? Inicializa una lista, L =DIRECCION DE MEMORIA
    L->maxSize= MAXSIZE;
    L->listSize=0; // El tamaño siempre sera 1 mas grande que la pos dl final de la lista
    L->curr=0; // EL cursor se inicializa 1 pos mas adelante que el ultimo elemento ingresado
    L->listArray= (tElemLista*)malloc((L->maxSize)*(sizeof(tElemLista)));
}

void clear(tLista *L){ //?  reinicializa la lista, dejandola inicializada pero vacia

    free(L->listArray);
    L->listSize=0;
    L->curr=0;
    L->listArray = malloc((L->maxSize)*(sizeof(tElemLista)));
}

int insert(tLista *L, tElemLista item){ //? Insertara un elemento en la lista, en la pos actual y nos retornara la pos en la que la inserto, o -1 si es que fue ml insertada
    if (L->curr >= L->maxSize || L->listSize >= L->maxSize){
        return -1;}
    unsigned int i=0;
    for ( i=L->listSize; i>L->curr; i--)
        L->listArray[i] = L->listArray[i-1];
    L->listArray[i]= item;
    L->listSize++;
    return (i);
}

int append(tLista *L, tElemLista item){ 
    if (L->listSize >= L->maxSize){
        return -1;}
    
    L->listArray[L->listSize]=item;
    L->listSize++;
    return 0;
}

tElemLista erase(tLista *L){ //? Borra el elemento donde este puesto el cursor, y lo retorna
    if (L->curr < 0 || L->curr >= L->listSize)
        return -1;
    tElemLista aux = L->listArray[L->curr];
    for (int i = L->curr; i<(L->listSize)-1; i++){ // se hace con -1 por que  
        L->listArray[i] = L->listArray[(i+1)];
    }
    L->listSize--;
    return aux;
}

void moveToStart(tLista *L){ //? Mover el cursor al inicio de la lista
    L->curr=0;
}

void moveToEnd(tLista *L){
    L->curr=(L->listSize); //COn esto el cursor queda en la pos de adelante del ultimo elemento de la lista
}

void moveToPos(tLista *L, int pos){
    L->curr==pos;
}

void prev(tLista *L)//? Mueve el cursor una posicion atras
{
    if (L->curr!=0){
        L->curr--;
    }
}

void next(tLista *L) //? Mueve el cursor una posicion adelante, pero nunca mas adelante que 'el tamaño de la lista'
{
    if (L->curr<L->listSize){
        L->curr++;
    }
}

void deleteList(tLista *L) //? Elimina la lista por completo
{
    free(L->listArray);
}

tElemLista getValue(tLista *L){ //? obtiene el valor del elemento actual de la lista
    tElemLista aux = L->listArray[L->curr];
    return aux;
}

int lenght(tLista *L){ //? Retorna el numero de elementos en la lista
    return(L->listSize);
}

int currPos(tLista* L){
    int aux=L->curr;
    return aux;
}
