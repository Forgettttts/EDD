#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 100

typedef int tElemLista;

typedef struct
{
    unsigned int maxSize;  // tamaño máximo de la lista
    unsigned int listSize; // tamaño actual de la lista
    unsigned int curr;     // posición actual de la lista
    tElemLista *listArray; // arreglo con los elementos de la lista
} tLista;

// inicializa una lista como vacía
void initList(tLista *L)
{
    L->maxSize = MAXSIZE; // tamaño máximo de la lista
    L->listSize = 0;      // lista vacía
    L->curr = 0;          //L->pos = 0;
    L->listArray = malloc(L->maxSize * sizeof(tElemLista));
}

// borra todos los elementos de la lista, reinicializándola vacía
void clear(tLista *L)
{
    free(L->listArray);
    L->listSize = L->curr = 0;
    L->listArray = malloc(L->maxSize * sizeof(tElemLista));
}

// inserta un elemento en la posición actual de la lista
int insert(tLista *L, tElemLista item)
{
    unsigned int i = 0;
    if (L->listSize >= L->maxSize)
        return -1; // lista de largo máximo no se llena
    for (i = L->listSize; i > L->curr; i--)
        L->listArray[i] = L->listArray[i - 1];
    L->listArray[i] = item;
    L->listSize++;
    // retorna posición de inserción
    return i;
}

// agrega un elemento al final de la lista
int append(tLista *L, tElemLista item)
{
    if (L->listSize >= L->maxSize)
        return 0;
    L->listArray[L->listSize++] = item;
    return 1;
}

// borra el elemento actual y retorna su valor
tElemLista erase(tLista *L)
{
    tElemLista item;
    int i;
    if (L->curr < 0 || L->curr >= L->listSize)
        return -1;
    item = L->listArray[L->curr];
    for (i = L->curr; i < L->listSize - 1; i++)
        L->listArray[i] = L->listArray[i + 1];
    L->listSize--;
    return item;
}

// mueve la posición actual al comienzo de la lista
void moveToStart(tLista *L)
{
    L->curr = 0;
}

// mueve la posición actual al final de la lista
void moveToEnd(tLista *L)
{
    L->curr = L->listSize;
}
// mueve la posición actual al elemento anterior de la lista
void prev(tLista *L)
{
    if (L->curr != 0)
        L->curr--;
}
// mueve la posición actual al elemento siguiente de la lista
void next(tLista *L)
{
    if (L->curr < L->listSize)
        L->curr++;
}
// elimina la lista, liberando memoria y recursos usados
void deleteLista(tLista *L)
{
    free(L->listArray);
}
