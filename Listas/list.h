
#define maxSize 1000000
#define invalid_element -12345

#include <stdio.h>
#include <stdlib.h>

typedef int tElemlista; //? es un entero, si no me equivoco, es algun elemento dentro de la lista que estamos trabajando
typedef struct
{
    unsigned int maxSize;  //? Tamaño amximo de la lista
    unsigned int listSize; //? Tamaño actual de la lista
    unsigned int curr;     //? Posicion actual del cursor dentro de la lista

    tElemLista *listArray; //?  puntero al elemento en la posicion curr del arreglo listArray de tamaño actual listSize
} tLista;

void initList(tLista *
typedef