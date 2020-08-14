#include <stdio.h>
#include <stdlib.h>

typedef int tElemenLista;

typedef struct{
    int max_size; //capacidad máxima del arreglo
    int curr;
    int list_size; //indica la cantidad de elementos que contiene la lista
    tElemenLista* list_Array;    
}tLista;

tLista rotate(tLista* L, int k){
    tLista rotada;
    initList(&rotada);
    int n = listSize(L);
    moveToPos(L, (n-k));
    for (int pos = currPos(L); pos < n; next(L))
    {
        tElemenLista elem = getValue(L);
        append(&rotada, elem);        
    }
    
    moveToStart(L);
    for (int curr = currPos(L); curr < (n-k); next(L))
    {
        tElemenLista elem = getValue(L);
        append(&rotada, elem);
    }
    return rotada;  
}