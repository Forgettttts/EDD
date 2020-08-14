#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//!                                                     ....:::: CERTAMEN 1 ::::....

//! ********************************* Problema 1.1 *********************************

typedef struct {
    char sigla[7];   /* por ejemplo, INF134 */
    int  nota;
} asignatura;

typedef struct {
    int Rol;
    int ingreso;     /* año de ingreso a la universidad */
    char nombre[31];
    asignatura ramos[50];
    int n_ramos;
} estudiante;

estudiante* enRiesgo(char* string, int A){
    char* parametro;
    strcpy(parametro, string);
    strcat(parametro, ".txt");
    FILE *fp;
    if(fopen(parametro, "rb")==NULL){
        printf("Error en la apertura del archivo\n");
    };
    int numero_structs;
    fread(numero_structs, sizeof(int), 1, fp); //! CANTIDAD DE STRUCTS A LEER

    estudiante* entrada= (estudiante*)malloc(sizeof(estudiante)*numero_structs); //! ARREGLO PARA LEER TODO
    estudiante salida[A]; //! ARREGLO RETORNO, SOLO GUARDA LOS QUE CUMPLEN CON LA CONDICION
    int contador_salida=0;
    int contador=0;
    while(fread( &entrada[0] , sizeof(estudiante), 1, fp)==1){
        int suma_notas=0; //!IRA ACUMULANDO LAS NOTAS DE LOS RAMOS
        for(int i=0; i<entrada[0].n_ramos; i++){
            suma_notas+=entrada[0].ramos[i].nota;
        }
        int promedio= suma_notas/entrada[0].n_ramos;
        if(entrada[0].ingreso==A && promedio<55){
            salida[contador_salida]=entrada[0]; //! SI CUMPLE CON LAS CONDICIONES, SE SUMA AL ARREGLO DE SALIDA
            contador_salida++; 
        }
        contador ++; 
    }

    free(entrada);
    return salida;
}

//! ********************************* Problema 1.2 *********************************

typedef struct {
    int rol_estudiante;
    int nota;
} notaevaluacion;

typedef struct {
    char nombre[31];
    char sigla[7];   /* por ejemplo, INF134 */
    int paralelo;
    notaevaluacion evaluaciones[500];
    int n_eval;
} paralelo;

//! ********************************* Problema 2.1 *********************************

typedef struct {
    int elementos[200]
    ;int n_elementos;       // numero de elementos
}conjunto;

conjunto initConjunto();
int hasElem(conjunto* C, int e);
int empty(conjunto* C);
int minElem(conjunto* C);
int nextElem(conjunto* C, int e);
void insertElem(conjunto* C, int e);

conjunto intersection(conjunto *C1, conjunto *C2){
    conjunto* retorno;
    initConjunto(retorno);
    for(conjunto actual=minElem(C1); hasElem(C1)!= True; actual=nextElem(C1, actual)){
        if(hasElem(C2, actual)){
            insertElem(retorno, actual);
        }
    }
}

//! ********************************* Problema 2.2 *********************************

conjunto difference(conjunto *C1, conjunto *C2){
    conjunto* retorno;
    initConjunto(retorno);
    for(conjunto actual=minElem(C1); hasElem(C1)!= True; actual=nextElem(C1, actual)){
        if(!(hasElem(C2, actual))){
            insertElem(retorno, actual);
        }
    }
}