#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
} clienteBanco;

int main()
{

    FILE *transacciones = fopen("transacciones.txt", "r");
    int monto;
    int monto2;
    char caracter;
    char caracter2;
    int **cuentas = (int **)malloc(sizeof(int *) * 4);
/*
    fscanf(transacciones, "%c %d %d %c %d %d ", &caracter, &cuentas[0], &monto, &caracter2, &cuentas[1], &monto2);
    printf("1) Cuentas: %d,  monto: %d\n 2) Cuentas: %d,  monto: %d\n", cuentas[0], monto, cuentas[1], monto2);
*/
    fscanf(transacciones, "%c %d %d\n", &caracter, &cuentas[0], &monto);
    /*
    fscanf(transacciones, "%d\n", &cuentas[0]);
    fscanf(transacciones, "%d\n", &monto);
*/
    printf("%d %d\n", cuentas[0], monto);

    fscanf(transacciones, "%c %d %d\n", &caracter, &cuentas[0], &monto);

    printf("%d %d\n", cuentas[0], monto );


    fclose(transacciones);

    return 0;
}