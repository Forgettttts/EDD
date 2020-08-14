#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDA_grafos.h"

#define NoVisitado 0
#define Visitado 1

int minimaCantidadRutas(tGrafo* G, int menos){
    for(int i=0; i<nVertex(G); i++){
        setMark(G, i, Visitado);
    }
    
    int comp_conexas=0;

    for (int i=0; i<nVertex(G); i++){
        if (i== NoVisitado){
            Djikstra(i);
            comp_conexas++;
        }
    }

    return (comp_conexas-1); //! ES -1 PQ SE PIDEN LAS MINIMAS ARISTAS QUE SE DEBEN AGREGAR
}