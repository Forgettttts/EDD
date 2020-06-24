#include <stdlib.h>
#include <stdio.h>
#define MAX_SIZE 10

typedef int telemQueue;

typedef struct
{ //[_, _, t, _, h, _]
    int ult, prim;
    telemQueue *Qarray;
    unsigned int maxsize;
} tQueue;

void init(tQueue *Q)
{
    Q->maxsize = MAX_SIZE;
    Q->Qarray = (telemQueue *)malloc(sizeof(telemQueue *) * Q->maxsize);
    Q->ult = -1;
    Q->prim = 0;
}

void clear(tQueue *Q)
{
    free(Q->Qarray);
    Q->Qarray = (telemQueue *)malloc(sizeof(telemQueue *) * Q->maxsize);
    Q->ult = -1;
    Q->prim = 0;
}

void delete (tQueue *Q)
{
    free(Q->Qarray);
    Q->ult = -1;
    Q->prim = -1;
}

int enqueue(tQueue *Q, telemQueue item)
{
    Q->ult++;
    if (Q->ult == Q->maxsize++ && Q->prim != 0) //circula
    {
        Q->ult = 0;
    }
    Q->Qarray[Q->ult] = item;
    return 1;
}

void dequeue(tQueue *Q)
{
    if (Q->prim == Q->maxsize)
    {
        Q->prim = 0;
    }
    Q->prim++;
}

void printQ(tQueue *Q)
{
    printf("[");
    if (Q->ult < Q->prim)
    {
        for (int i = Q->prim; i < Q->maxsize; i++)
        {
            printf("%d, ", Q->Qarray[i]);
        }
        for (int k = 0; k <= Q->ult; k++)
        {
            printf("%d, ", Q->Qarray[k]);
        }
        puts("]");
    }
    else
    {
        for (int j = Q->prim; j <= Q->ult; j++)
        {
            printf("%d, ", Q->Qarray[j]);
        }
        puts("]");
    }
}

int isEmpty(tQueue *Q)
{
    if (Q->ult == -1)
        return 1;
    else if (Q->prim == Q->ult)
        return 1;
    return 0;
}

int isFull(tQueue *Q)
{
    if (Q->ult++ == Q->prim)
        return 1;
    else if (Q->prim == 0 && Q->ult == Q->maxsize)
        return 1;
    return 0;
}

telemQueue frontValue(tQueue *Q)
{
    return Q->Qarray[Q->prim];
}

int size(tQueue *Q)
{
    if (Q->ult < Q->prim)
        return (Q->maxsize - Q->prim) + Q->ult;
    else
    {
        int res = (Q->ult - Q->prim);
        return res++;
    }
}