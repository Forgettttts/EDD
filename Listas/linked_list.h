#include <stdlib.h>
#include <stdio.h>

typedef int tElemLista;

typedef struct nodo{
    tElemLista info;
    struct nodo *sig; //* Este es un puntero a un elemento tipo tNodo, pero omo aunn no le damos ese nombre, tenemos que llamarlo por struct nodo, que es el nombre real
}tNodo;

typedef struct{
    tNodo *head;
    tNodo *tail;
    tNodo *curr;
    unsigned int listSize;
    unsigned int pos; // posición actual en la lista
}tLinkedList