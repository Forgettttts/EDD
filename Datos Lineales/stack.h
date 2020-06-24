#include <stdlib.h>
#define MAXSIZE 1000000


//? Una pila es una lista, con la diferencia de que en una pila solo puedes trabajar con el ultimo elemento
typedef int tElemPila;

typedef struct
{
    unsigned int maxSize;  // tamaño maximo de la pila
    unsigned int top;      // tamaño actual de la pila
    tElemPila *stackArray; // arreglo con los elementos de la pila
} tPila;

void initStack(tPila *P)//? Inicializa una pila
{
    P->maxSize = MAXSIZE;
    P->top = -1; //! Se inicializa en -1 ya que esto siempre tiene que apuntar a la posicion del tope de la lista en el arreglo de la pila, por lo que una lista de 1 elemento, tendra poscion de tope =0 
    P->stackArray = (tElemPila*)malloc(P->maxSize * (sizeof(tElemPila)));
};

int push(tPila *P, tElemPila item) //? Inserta un elemento en el tope de la pila
{
    if (P->top == P->maxSize)
        return 1; //* Si es que el la pila ya tiene el tamaño maximo, no se pueden agragar ams elementos, o si no habra un overflow
    P->top++;
    P->stackArray[P->top] = item;
    return 0; //* Si es que la inserción es exitosa, retorna 0
}

void clear(tPila *P) //? Reinicializa una pila como vacía
{
    free(P->stackArray); //* Liberamos la memoria solicitada para el arreglo pila
    P->top = -1; //* Seteamos el tope de la lista en -1, para indicar que no hay elementos en la lista
    P->stackArray = (tElemPila *)malloc(P->maxSize * (sizeof(tElemPila))); //* Pedimos nuevamente el espacio para usar el arrreglo de nuevo
}

tElemPila pop(tPila *P) //? Elimina el elemento que está en el tope de la pila, retornandolo
{
    if (P->top >= 0)
    {
        tElemPila t = P->stackArray[P->top]; //* Se copia el elemento del tope de la lista, en una variable auxiliar, la cual sera retornada
        P->top--; //* Simplemente disminuimos el largo de la lista en 1, perdiendo asi el ultimo elemento
        return t;
    }
}

tElemPila topValue(tPila *P) //? Retorna el elemento que está en el tope de la pila
{
    return P->stackArray[P->top];
}

int size(tPila *P) //? Retorna el tamaño de una pila
{
    return P->top++;
}

void deleteStack(tPila *P)
{
    free(P->stackArray);
    P->top = -1;
    //* No pide mas memoria, ya que este borra la pila, sin dejar rastro
}                             