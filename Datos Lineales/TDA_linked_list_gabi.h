#include <stdlib.h>
#include <stdio.h>

typedef int tElemLista;

typedef struct nodo
{
    tElemLista info;
    struct nodo *sig;
} tNodo;

typedef struct
{
    tNodo *head;
    tNodo *tail;
    tNodo *curr;
    unsigned int listSize;
    unsigned int pos; // posición actual en la lista
} tLista;

void initList(tLista *L)
{
    L->head = L->tail = L->curr = (tNodo *)malloc(sizeof(tNodo));
    L->listSize = 0;
    L->pos = 0;
}

void clear(tLista *L)
{
    tNodo *next;
    L->curr = L->head;
    while (L->curr != NULL)
    {
        next = L->curr->sig;
        free(L->curr);
        L->curr = next;
    }
    L->head = L->tail = L->curr = (tNodo *)malloc(sizeof(tNodo));
    L->listSize = 0;
    L->pos = 0;
}

void erase(tLista *L)
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
// inserta un elemento en la posición actual de la lista
int insert(tLista *L, tElemLista item)
{
    tNodo *aux = L->curr->sig;
    L->curr->sig = (tNodo *)malloc(sizeof(tNodo));
    L->curr->sig->info = item;
    L->curr->sig->sig = aux;
    if (L->curr == L->tail)
        L->tail = L->curr->sig;
    L->listSize++;
    return L->pos;
}

void moveToStart(tLista *L)
{
    L->curr = L->head;
    L->pos = 0;
}

void moveToEnd(tLista *L)
{
    L->curr = L->tail;
    L->pos = L->listSize;
}

void prev(tLista *L)
{
    tNodo *temp;
    if (L->curr == L->head)
        return;
    temp = L->head;
    while (temp->sig != L->curr)
    {
        temp = temp->sig;
    }
    L->curr = temp;
    L->pos--;
}
void next(tLista *L)
{
    if (L->curr != L->tail)
    {
        L->curr = L->curr->sig;
        L->pos++;
    }
}

void moveToPos(tLista *L, unsigned int posicion)
{
    unsigned int i;
    if (posicion < 0 || posicion > L->listSize)
        return;
    L->curr = L->head;
    L->pos = 0;
    for (i = 0; i < posicion; i++)
    {
        L->curr = L->curr->sig;
        L->pos++;
    }
}

//!Hasta acá son del ppt. de ahora en adelante son creadas por mí c:

void printList(tLista *L)
{
    moveToStart(L);
    printf("[");
    int n = L->listSize;
    n--;
    for (int i = 0; i < n; i++)
    {
        printf("%d ,", L->curr->info);
        L->pos++;
        L->curr = L->curr->sig;
    }
    printf("%d]\n", L->curr->sig->info);
    moveToEnd(L);
}
