#include <stdlib.h>
#define MAXSIZE 1000

typedef int tElemPila;

typedef struct
{
    unsigned int maxSize;  // tamaño maximo de la pila
    unsigned int top;      // tamaño actual de la pila
    tElemPila *stackArray; // arreglo con los elementos de la pila
} tPila;

// inicializa una nueva lista vacía
void initStack(tPila *P)
{
    P->maxSize = MAXSIZE;
    P->top = -1;
    P->stackArray = malloc(P->maxSize * (sizeof(tElemPila)));
};

//inserta un elemento en el tope de la pila
int push(tPila *P, tElemPila item)
{
    if (P->top == P->maxSize)
        return 0;
    P->top++;
    P->stackArray[P->top] = item;
    return 1; // inserción exitosa
}

// reinicializa una pila como vacía
void clear(tPila *P)
{
    free(P->stackArray);
    P->top = -1;
    P->stackArray = malloc(P->maxSize * (sizeof(tElemPila)));
}

// elimina el elemento que está en el tope de la pila y lo retorna.
tElemPila pop(tPila *P)
{
    if (P->top >= 0)
    {
        tElemPila t = P->stackArray[P->top];
        P->top--;
        return t;
    }
}

// retorna una copia del elemento que está en el tope de la pila
tElemPila topValue(tPila *P)
{
    return P->stackArray[P->top];
}

// retorna el tamaño de una pila
int size(tPila *P)
{
    return P->top++;
}

void delete (tPila *P)
{
    free(P->stackArray);
    P->top = -1;
}
