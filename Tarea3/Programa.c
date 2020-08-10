#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MaxHeap.h"
#include "HASH_OFERTA.h"
#include "HASH_PRODUCTO.h"

int main(){

    FILE* Arch_productos = fopen("productos.dat", "rb");
    if (Arch_productos == NULL){
        printf("Problema de apertura de archivo productos.dat, finalizacion anticipada del programa");
        return 1;
    }

    FILE* Arch_ofertas = fopen("ofertas.dat", "rb");
    if (Arch_ofertas == NULL){
        printf("Problema de apertura de archivo ofertas.dat, finalizacion anticipada del programa");
        return 1;
    }

    FILE* Arch_compras = fopen("compras.txt", "r");
    if (Arch_compras == NULL){
        printf("Problema de apertura de archivo compras.txt, finalizacion anticipada del programa");
        return 1;
    }

    int N_of;
    int N_prod;
    fread(&N_of, sizeof(int), 1, Arch_ofertas);
    fread(&N_prod, sizeof(int), 1, Arch_productos);
    int M_of = calcular_M_of(N_of);
    int M_prod = calcular_M_prod(N_prod);

    ranuraOferta* TablaOfertas;
    ranuraProducto* TablaProductos;
    init_Tabla_Oferta(&TablaOfertas, N_of);
    init_Tabla_Productos(&TablaProductos, N_prod);
    
    
    oferta Temp;
    for (int i = 0; i < N_of; i++)
    {
        fread(&Temp, sizeof(oferta), 1, Arch_ofertas);
        HashInsertOferta(&TablaOfertas, Temp.codigo_producto, Temp, M_of);
    }
    
    producto Aux;
    for (int i = 0; i < N_prod; i++)
    {
        fread(&Aux, sizeof(producto), 1, Arch_productos);
        HashInsertProducto(&TablaProductos, Aux.codigo_producto, Aux, M_prod);
    }

    int R;
    fscanf(Arch_compras, "%d", &R);
    Heap* Ranking;
    init_Max_Heap(&Ranking, R);

    int clientes;
    fscanf(Arch_compras, "%d", &clientes);

    for (int i = 0; i < clientes; i++)
    {
        int cantidad_prod;
        fscanf(Arch_compras, "%d", &cantidad_prod);
        for (int k = 0; k < cantidad_prod; k++)
        {
            tipoClave codigo;
            fscanf(Arch_compras, "%d", &codigo);
            producto Prod_actual = HashSearchProducto(&TablaProductos, codigo, M_prod);
            oferta Of_actual = HashSearchOferta(&TablaOfertas, codigo, M_of);
            
            //! OPCION 1: Hacer que un campo de los structs de producto contabilice la cantidad de productos que el 
            //!           cliente lleva

            //!OPCION 2: Hacer una tabla de hashing, la clave sera el codigo de los produtos, y la info sera cuantos 
            //!          productos de esos esta llevando el cliente
            


            /*
            if (Prod_actual.codigo_producto != Of_actual.codigo_producto) //Si los codigos son distintos es porque no hay ofertas para ese producto.
            {
                code 
            }
            */
        }
        }
        
    }
    
















    return 0;
}