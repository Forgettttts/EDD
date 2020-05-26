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
    clienteBanco alan = {123456, 0, "Alancito", "Puente"};
    clienteBanco alonso = {234567, 0, "Alonsnsito", "Nuñoa"};
    clienteBanco varo = {345678, 0, "Vararito", "Buin"};
/*
    printf("cuenta=%d, saldo=%d, nombre=%s, direccion=%s \n", alan.nroCuenta, alan.saldo, alan.nbre, alan.direccion);
    printf("cuenta=%d, saldo=%d, nombre=%s, direccion=%s \n", alonso.nroCuenta, alonso.saldo, alonso.nbre, alonso.direccion);
    printf("cuenta=%d, saldo=%d, nombre=%s, direccion=%s \n", varo.nroCuenta, varo.saldo, varo.nbre, varo.direccion);

    clienteBanco **CL = (clienteBanco **)malloc(sizeof(clienteBanco *) * 3);
    CL[0]=(clienteBanco*)sizeof(clienteBanco);
    CL[2]=(clienteBanco*)sizeof(clienteBanco);
    CL[1]=(clienteBanco*)sizeof(clienteBanco);

    CL[0] = &alan;
    CL[1] = &alonso;
    CL[2] = &varo;

    printf("id alan=%d \n", CL[0]->nroCuenta);
    FILE *fp= fopen("test.dat", "wb");
    fwrite( CL[0],sizeof(clienteBanco) ,1 , fp);
    */
   clienteBanco *CL=malloc(sizeof(clienteBanco)*3);
   CL[0] = (clienteBanco){123456, 0, "Alancito", "Puente"};
   CL[1] = (clienteBanco){234567, 0, "Alonsnsito", "Nuñoa"};
   CL[2] = (clienteBanco){345678, 0, "Vararito", "Buin"};
   FILE *fp = fopen("test.dat", "wb");
   fwrite(CL, sizeof(clienteBanco), 3, fp);

   return 0;
}