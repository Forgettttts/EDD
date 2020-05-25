#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
} clienteBanco;

clienteBanco** actualizarSaldos(char* clientes, char* transacciones){

    FILE *transa =fopen(transacciones, "r");
    fscanf

    clienteBanco** actualizacion; // Arreglo de punteros a Structs de tipo clienteBanco

    FILE *Archibi = fopen(clientes, "rb+");
    
    while (fread(actualizacion, sizeof(clienteBanco*), 1, Archibi) == 1)
        



    return actualizacion;
}


int main(){ 









    
}

