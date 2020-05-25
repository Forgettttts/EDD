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

/*********
 * Nombre función: Buscar
 * Tipo función: tipo entero (int)
 *********
* Resumen:
    Esta función busca un número de cuenta, dentro de un arreglo de clientes del banco (clienteBanco)
    invocando a la función busqueda_binaria.
 *********
* Inputs:
    clienteBanco** vector : es un arreglo de punteros a structs de tipo clienteBanco.
    int buscame : es el numero de cuenta que a ecnontrar.
    int tamvector : es el tamaño del arreglo de clientes del banco.
 *********
* Returns:
    retorna el resultado de invocar a la función busqueda_binaria; spoiler: es un entero.
*********/
int buscar(clienteBanco **vector, int buscame, int tamvector) // Buscaremos en que posicion esta el struct que contiende los datos del cliente, gracias a una busqueda binaria
{
    return busqueda_binaria(vector, buscame, 0, tamvector - 1);
}

//? BORRAR ESTOOOOO! Cuando hagamos el arreglo de structs necesitamos un contador que vaya diciendo el largo del arreglo

/*********
 * Nombre función: Busque_binaria
 * Tipo función: tipo entero (int)
 *********
* Resumen:
    Esta función busca un número de cuenta, dentro de los campos de un arreglo de clientes 
    del banco (clienteBanco) usando el método de búsqueda binaria, para ello, se invoca 
    recursivamente.
 *********
* Inputs:
    clienteBanco** listastruct : es un arreglo de punteros a structs de tipo clienteBanco.
    int buscame : es el número de cuenta que a ecnontrar.
    int inicio : es el número que epresenta la posición desde donde se comienza a buscar en el arreglo.
    int fin : es el número que representa la posición hasta la que se termina de buscar en el arreglo.
 *********
* Returns:
    int pos : es el número que representa la posición dentro del arreglo de clientes, en donde se encuentra
    el cliente cuyo númera de cuenta buscábamos.
*********/

int busqueda_binaria(clienteBanco **listastruct, int buscame, int inicio, int fin)
{

    // Para encointrar el punto medio del arreglo
    int ptomedio = inicio + (fin - inicio) / 2;

    if (inicio > fin) // Esto es en el caso de que se hayan ingresado mal el orden de los parametros
    {
        return -1;
    }
    else if ((listastruct[ptomedio]->nroCuenta) == buscame) // esto es en el caso de que se encuentre inmediatamente el elemento buscado
    {
        return ptomedio;
    }
    // Si el nroCuenta actual (en el que estamos posicionados) es mayor que buscame, buscamos en la mitad inferior
    else if ((listastruct[ptomedio]->nroCuenta) > buscame)
    {
        // Mitad inferior = desde inicio hasta ptomedio-1
        return busqueda_binaria(listastruct, buscame, inicio, ptomedio - 1);
    }
    // Si el nroCuenta actual (en el que estamos posicionados) es menor que buscame, buscamos en la mitad superior
    else
    {
        // Mitad superior = desde ptomedio+1 hasta fin
        return busqueda_binaria(listastruct, buscame, ptomedio + 1, fin);
    }
}

actualizarSaldos(char *clientes, char *transacciones)
{
    clienteBanco **listastruct = (clienteBanco **)malloc(sizeof(clienteBanco *) * 10000000); //! Aqui creariamos el arreglo de punteros tipo clienteBanco
    listastruct[i] = (clienteBanco *)malloc(sizeof(clienteBanco));
}

int main(int argc, char** argv) //argc= cantidad de elementos que se estan ingresando, **argv= arreglo de strings ingresados
{
    FILE *transacciones = fopen("transacciones.txt", "r");
    if (transacciones == NULL) //revisamos si es que el archivo se abrio bien
    {
        printf("Error al abrir el archivo de las transacciones, fin anticipado del programa"); 
        return 1;
    }
    
    int *cuentas = (int *)malloc(sizeof(int) * 2); //Aqui guardaremos el(los) numero(s) de cuenta(s) que implica la transaccion actual
    int monto, pos; //En monto se guardara cuanto es el monto de dinero involucrado en esta transaccion, y pos es la posicion del cliente dentro del conjunto de structs clientebanco
    char operador; // este indica si es que es deposito(+), extraccion(-) o transferencia(>) 
    fscanf(transacciones, "%c", &operador); // va con & ya que solo es un caracter, no un arreglo

    while (operador != EOF)
    {

        if (operador == '+')
        {
            fscanf(transacciones, "%d %d\n", &cuentas[0], &monto);
            pos = buscar(CL, cuentas[0], tamCL); //!CREAR ARREGLO DE STRUCTS CLIENTES DE BANCO Y SU TAMAÑO TAMCL
            CL[pos]->saldo += monto;
        }

        else if (operador == '-')
        {
            fscanf(transacciones, "%d %d\n", &cuentas[0], &monto);
            pos = buscar(CL, cuentas[0], tamCL); //!CREAR ARREGLO DE STRUCTS CLIENTES DE BANCO Y SU TAMAÑO TAMCL
            CL[pos]->saldo -= monto;
        }

        else if (operador == '>')
        {
            fscanf(transacciones, "%d %d %d\n", &cuentas[0], &cuentas[1], &monto);
            pos = buscar(CL, cuentas[0], tamCL);
            CL[pos]->saldo -= monto;
            pos = buscar(CL, cuentas[1], tamCL);
            CL[pos]->saldo += monto;
        }
    }

    return 0;
}
