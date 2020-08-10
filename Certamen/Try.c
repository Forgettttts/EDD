#include <stdio.h>
#include <stdlib.h>
#include "TDA_grafos.h" //? Este es el header con las funciones del TDA

tVertice masSaturado(tGrafo *G){
    int *entradas, *salidas;
    int n= nVertex(G);
    tVertice a, b; 
    entradas= (int*)malloco(sizeof(int)*n); // Arreglo para almacenar el flujo de entrada de cada nodo
    salidas = (int *)malloco(sizeof(int) * n); //Arreglo para almacenar el flujo de salida de cada nodo
    for (a = 0; a < n; a++)
    {
        for (b=first(G, a); b < n; b=next(G, a, b))
        {
            // A los nodos que salen de a, llegando a b, se les sumara en su posicion del arreglo entrada, el peso
            // del arco de entrada correspondiente
            entradas[b]+=weight(G, a, b);
            // Al nodo desde el que sale el arco, se le sumara en su posicion del arreglo salida, el peso del arco 
            // de salida correspondiente
            salidas[a] += weight(G, a, b);
        }
    }
    tVertice mas_saturado=0;
    int saturacion=0;
    
    for (a = 0; a < n; a++)
    {
        if (((entradas[a] - salidas[a]) > saturacion) && ((entradas[a] - salidas[a]) >0))
        {
            mas_saturado=a;
            saturacion = (entradas[a] - salidas[a]);
        }
    }
    free(entradas);
    free(salidas);
    return mas_saturado;
    }
