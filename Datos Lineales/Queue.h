#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000000

typedef int tElemQueue;

typedef struct //? Struct de una cola
{ //[_, _, t, _, h, _]
    int ult, prim;
    telemQueue *Qarray;
    unsigned int maxsize;
} tQueue;

void init(tQueue *Q) //? Inicializar una cola
{
    Q->maxsize = MAX_SIZE;
    Q->Qarray = (telemQueue *)malloc(sizeof(telemQueue *) * Q->maxsize);
    Q->prim = -1; //* prim = Primero = Extremos izquierdo = Primer elemento que entram = Primero que sale
    Q->ult =0 ; //* ult = Ultimo = Extremo dercho = ultimo elemento que entra = Ultimo que sale 
}

void clear(tQueue *Q) //? Limpiamos la queue, liberamos memoria y la reinicializamos, pidiendo memoria nueva.
{
    free(Q->Qarray);
    Q->Qarray = (telemQueue *)malloc(sizeof(telemQueue *) * Q->maxsize);
    Q->prim = -1;
    Q->ult = 0;
}

void deleteQueue(tQueue *Q) //? Limpiamos la queue, liberando memoria, no pedimos mas memoria pq la borramos
{
    free(Q->Qarray);
    Q->ult = -1;
    Q->prim = -1;
}

int enqueue(tQueue *Q, tElemQueue item) //? Ingresa un elemento al final de esta cola, retorna 0 en cao de sere citosa la insercion
{
    Q->ult++; //* Hacemos que el ultimo elemento avance
    //* En caso de que el ultimo elemento ya haya alcanzado el tamaño maximo (Por restriccion, no puede ser mayor), y ademas
    //* el primer elemento no esta en la posicion 0(ya salio algun elemento), podremos insertar el elemnto al principio (QUEUE CIRCULAR)
    if (Q->ult == Q->maxsize++ && Q->prim != 0) 
    {
        Q->ult = 0;
    }
    Q->Qarray[Q->ult] = item;
    return 0;
}

tElemQueue dequeue(tQueue *Q) //? Elimina el primer elemento de la cola, retorna el elemento eliminado, si es que la eliminacion fue exitosa
{
    tElemQueue aux = Q->Qarray[Q->prim];
    if (Q->prim == Q->maxsize)
    {
        Q->prim = 0;
        return aux; //* Si es que el elemento prim esta al final, al tope de la queue, simplemente lo movemos al incio de la cola, perdiendo asi el dato que queda al final
    }
    Q->prim++; //* Si es que no estaba al final, simplemente avanzamos, perdiendo asi el elemento que queremos perder
    return aux;
}

void printQ(tQueue *Q) //? Printeara los elementos del queue
{
    printf("[");
    if (Q->ult < Q->prim) //* Si es que el prim esta despeus del ult
    {
        for (int i = Q->prim; i < Q->maxsize; i++) //* Primero leeremos los elementos que fueron insertados primero
        {
            printf("%d, ", Q->Qarray[i]);
        }
        for (int k = 0; k <= Q->ult; k++)
        {
            printf("%d, ", Q->Qarray[k]);
        }
        puts("]");
    }
    else //* Si es que el prim esta antes del ult
    {
        for (int j = Q->prim; j <= Q->ult; j++) //* Printaremos los elementos en orden de insercion, desde el prim, al ult
        {
            printf("%d, ", Q->Qarray[j]);
        }
        puts("]");
    }
}

int isEmpty(tQueue *Q)//? Chequea si es que la queue esta vacia, retorna 0 si es que si, o 1 si es que no
{
    if (Q->prim==-1 && Q->ult==0) //* Si es que nunca se inserto nada, ta vacio
        return 0;
    else if (Q->prim == Q->ult)//* Si es que estan en la misma posicion, es pq ta vacio 
        return 0;
    return 1;
}

int isFull(tQueue *Q) //? Si es que esta lleno, retorna 0, si no, 1
{
    if (Q->ult++ == Q->prim)
        return 0;
    else if (Q->prim == 0 && Q->ult == Q->maxsize)
        return 0;
    return 1;
}

tElemQueue frontValue(tQueue *Q) //? Printea el primer elemento de la queue
{
    return Q->Qarray[Q->prim];
}

int size(tQueue *Q)//? Printea la cantidad de elementos del queue
{
    if (Q->ult < Q->prim)
        return (Q->maxsize - Q->prim) + Q->ult;
    else
    {
        int res = (Q->ult - Q->prim);
        return res++;
    }
}