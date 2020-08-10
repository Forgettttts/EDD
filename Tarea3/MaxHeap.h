#include <stdio.h>
#include <stdlib.h>

typedef int tipoClave; //vamos a definir las claves como nros enteros, (Para el problema, clave es codigo_producto)


typedef struct { // Definición del TIPO producto en venta
    tipoClave codigo_producto;
    char nombre_producto[31];
    int cantidad;
    int monto;
}productoHeap; // Los productos deben almacenarse en un HASHING CERRADO


typedef struct
{
    int ranking_size; //Tamaño actual del ranking (posiciones ocupadas, o cantidad de nodos insertados)
    productoHeap* array;
}Heap;


void init_Max_Heap(Heap* Ranking, int R){ //Crear un arreglo de tamaño L, con capacidad para almacenar productos de heap
    Ranking->ranking_size = 0;
    Ranking->array = (productoHeap*)malloc(sizeof(productoHeap)*R);
}


void insert_in_Heap(Heap* Ranking, productoHeap Prod){
    int pos = Ranking->ranking_size;
    Ranking->array[++pos] = Prod;
    Ranking->ranking_size++;

    while (Ranking->array[pos/2].monto < Ranking->array[pos].monto)
    {
        productoHeap padre_auxiliar = Ranking->array[pos/2];
        Ranking->array[pos/2] = Ranking->array[pos];
        Ranking->array[pos] = padre_auxiliar;
        pos = pos/2;
    }    
}


void delete_Max_Heap(Heap* Ranking){
    free(Ranking->array);
}