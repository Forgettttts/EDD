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

//Solo incializamos aqui las funciones, para evitar problemas o warnings en el codigo mas adelante
int busqueda_binaria(clienteBanco **listastruct, int buscame, int inicio, int fin);
int buscar(clienteBanco **vector, int buscame, int tamvector);
void actualizarSaldos(char *clientes, char *transacciones);

int busqueda_binaria(clienteBanco **listastruct, int buscame, int inicio, int fin)
{
    /*********
 * Nombre función: Busqueda_binaria
 * Tipo función: Tipo entero (int)
 *********
* Resumen:
    Esta función busca un número de cuenta, dentro de los campos de un arreglo de clientes 
    del banco (clienteBanco) usando el método de búsqueda binaria, para ello, se invoca 
    recursivamente.
 *********
* Inputs:
    clienteBanco** listastruct : Es un arreglo de punteros a structs de tipo clienteBanco.
    int buscame : Es el número de cuenta que a encontrar.
    int inicio : Es el número que representa la posición desde donde se comienza a buscar en el arreglo.
    int fin : Es el número que representa la posición hasta la que se termina de buscar en el arreglo.
 *********
* Returns:
    int pos : Es el número que representa la posición dentro del arreglo de clientes, en donde se encuentra
    el cliente cuyo númera de cuenta buscábamos.
*********/


    // Definitremos ptomedio, para encointrar el punto medio del arreglo
    int ptomedio = inicio + (fin - inicio) / 2;

    if (inicio > fin) { // En caso de que se hayan ingresado mal el orden de los parametros
        return -1;
    }
    else if ((listastruct[ptomedio]->nroCuenta) == buscame) {
       // En el caso de que se encuentre inmediatamente el elemento buscado
        return ptomedio;
    }
    // Si el nroCuenta actual (en el que estamos posicionados) es mayor que buscame, buscamos en la mitad inferior
    else if ((listastruct[ptomedio]->nroCuenta) > buscame) {
        // Mitad inferior = desde inicio hasta ptomedio-1
        return busqueda_binaria(listastruct, buscame, inicio, ptomedio - 1);
    }
    // Si el nroCuenta actual (en el que estamos posicionados) es menor que buscame, buscamos en la mitad superior
    else {
        // Mitad superior = desde ptomedio+1 hasta fin
        return busqueda_binaria(listastruct, buscame, ptomedio + 1, fin);
    }
}

int buscar(clienteBanco **vector, int buscame, int tamvector) {
    /*********
 * Nombre función: Buscar
 * Tipo función: Tipo entero (int)
 *********
* Resumen:
    Esta función busca un número de cuenta, dentro de un arreglo de clientes del banco (clienteBanco)
    invocando a la función busqueda_binaria.
 *********
* Inputs:
    clienteBanco** vector : Es un arreglo de punteros de tipo clienteBanco(struct) a structs de tipo clienteBanco.
    int buscame : Es el numero de cuenta que a encontrar.
    int tamvector : Es el tamaño del arreglo de clientes del banco.
 *********
* Returns:
    Retorna la posicion de el struct en el que esta contenido el numero de cuenta buscado, resultado de invocar a 
    la función busqueda_binaria.
*********/
    return busqueda_binaria(vector, buscame, 0, tamvector - 1);
}

void actualizarSaldos(char *clientes, char *transacciones)
{
    /*********
 * Nombre función: actualizar_saldos
 * Tipo función: void
 *********
* Resumen: 
    Esta función actualiza el saldo de los clientes contenidos en un archivo binario, esto lo realiza, abriendo el archivo, 
    guardando los clientes del banco en el arreglo CL (arreglo tipo clientesBanco(struct) de punteros tipo clientesBanco(struct)),
    modificando sus saldos según las operaciones realizadas por los clientes (descritas en un archivo ASCII de transacciones
    bancarias), para luego sobreescribir el archivo binario según arreglo actualizado.
 *********
* Inputs:
    char *clientes : Es un string que representa el nombre deL archivo binario que contiene structs de tipo clienteBanco.
    char *transacciones : Es un string que representa el nombre deL archivo ASCII, que contiene las transacciones realizadas
    por los clientes.
 *********
* Returns:
    No retorna nada, pues esta función sólo actualiza, sobreescribiendo el archivo de clientes, actualizando sus respectivos saldos.
*********/


    // Abrimos el archivo binario clientes.
    FILE *nombin = fopen(clientes, "rb");
    if (nombin == NULL) //revisamos si es que el archivo se abrio bien
    {
        printf("Error al abrir el archivo de clientes, fin anticipado del programa"); 
        exit(1);
    }
    

    clienteBanco **CL = (clienteBanco**)malloc(sizeof(clienteBanco *) * 10000000); //armamos arreglo de putneros tipo clientesBanco
    int tamCL=0; //Este contador nos dira la posicion actual de la iteracion del arreglo CL, lo cual nos servira para saber el nro. de elemetnos
    CL[tamCL]=(clienteBanco*)malloc(sizeof(clienteBanco)); //Asignamos memoria al puntero actual
    while (fread(CL[tamCL], sizeof(clienteBanco), 1, nombin)==1){
        tamCL++; //Avanzamos en el arreglo
        CL[tamCL] = (clienteBanco *)malloc(sizeof(clienteBanco));//Asignamos memoria al puntero actual
    }
    realloc(CL, sizeof(clienteBanco*)*tamCL);
    fclose(nombin);


    // Abrimos el archivo ASCII de transacciones.
    FILE *nomtranx = fopen(transacciones, "r");
    if (nomtranx == NULL) //revisamos si es que el archivo se abrio bien
    {
        printf("Error al abrir el archivo de las transacciones, fin anticipado del programa"); 
        exit (1);
    }
    
    int *cuentas = (int *)malloc(sizeof(int) * 2); //Aqui guardaremos el(los) numero(s) de cuenta(s) que implica la transaccion actual
    int monto, pos; //En monto se guardara cuanto es el monto de dinero involucrado en esta transaccion, y pos es la posicion del cliente dentro del conjunto de structs clientebanco
    char operador; // este indica si es que es deposito(+), extraccion(-) o transferencia(>) 

    while ((fscanf(nomtranx, "%c", &operador)) != EOF)
    {
        if (operador == '+')
        {
            fscanf(nomtranx, "%d %d\n", &cuentas[0], &monto);
            pos = buscar(CL, cuentas[0], tamCL); 
            CL[pos]->saldo += monto;
            
        }

        else if (operador == '-')
        {
            fscanf(nomtranx, "%d %d\n", &cuentas[0], &monto);
            pos = buscar(CL, cuentas[0], tamCL); 
            CL[pos]->saldo -= monto;
        }

        else if (operador == '>')
        {
            fscanf(nomtranx, "%d %d %d\n", &cuentas[0], &cuentas[1], &monto);
            pos = buscar(CL, cuentas[0], tamCL);
            CL[pos]->saldo -= monto;
            pos = buscar(CL, cuentas[1], tamCL);
            CL[pos]->saldo += monto;
        }
        else{
            printf("No es ninguno de los casos anteriores");
            exit(1);
        }
    }
    fclose(nomtranx);



    FILE *CLIENTES_ACTUALIZADOS = fopen(clientes, "wb");
    for (int i = 0; i < tamCL; i++)
    {
        fwrite( CL[i], sizeof(clienteBanco), 1, CLIENTES_ACTUALIZADOS );
    }
    fclose(CLIENTES_ACTUALIZADOS);
    
    for (int i=0; i<tamCL; i++){
        free(CL[i]);
    }
    free(CL);
    free(cuentas[1]);
    free(cuentas[0]);
}

int main(int argc, char** argv) 
{
    /*********
    * Nombre función: main
    * Tipo función: Tipo entero (int)
 *********
* Resumen:
    *Esta funcion actualiza los saldos de las cuentas que han tenido algun tipo de abono, transaccion o retiro
 *********
* Inputs:
    *argc: Cantidad de elementos en nuestro actualizarSaldos (nos retorna un int)
    *argv: Arreglo de strings en nuestro actualizarSaldos 
 *********
* Returns:
    * Actualiza los saldos de los clientes que han tenido un abono, retiro o transaccion
*********/

    //argc= cantidad de elementos que se estan ingresando, **argv= arreglo de strings ingresados
    if (argc !=3){
        printf("Se necesitan 2 argumentos a parte del nombre del programa, finalizacion anticipada del programa");
        return 2;
    }
    
    actualizarSaldos(argv[1], argv[2]);

    return 0;
    

}