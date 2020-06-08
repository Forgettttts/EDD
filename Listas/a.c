#include <stdio.h>
#include "list.h"


int main(){
    tLista L;
    initList(&L);
    tElemLista elem; // ... insertar elementos en la lista
    for (moveToStart(&L); currPos(&L) < length(&L); next(&L)) {
        elem = getValue(&L);
        hacerAlgo(elem);
        }deleteList(&L);
    return 0;
}