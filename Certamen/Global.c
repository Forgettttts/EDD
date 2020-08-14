#include <stdio.h>
#include <stdlib.h>
#include "TDA_grafos.h" //? Este es el header con las funciones del TDA


tVertice MasSeguidores(tGrafo *G) {
    int *influ;
    int n = nVertex(G); //cantidad de vertices en el grafo
    tVertice i, w, mas_seguidores;
    influ = (int *)malloc(sizeof(int)*n); // Arreglo donde se almacenara la cantidad de seguidores de cada persona
    for (i = 0; i < n; i++){ // Recorremos el grafo, nodo por nodo
        for (w = first(G, i) ; w < n ; w = next(G, i, w)){ // EL next tan solo entrega los arcos que salen de ese vertice
            influ[w]++;} // Como w es un nodo al cual llega un arco naciente en i, significa que i sigue a w, por ende a w se le suma un follower
    }
    int seguidores;
    for ( i = 0; i < n; i++){
        if (i==0){ // Secuencia de control para almacenar un parametro con el cual comparar los seguidores futuros
            mas_seguidores=i;
            seguidores= influ[i];
        }
        else{
            if(influ[i]>seguidores){
                mas_seguidores=i;
                seguidores=influ[i];}}}
    free(influ);
    return mas_seguidores;
    }