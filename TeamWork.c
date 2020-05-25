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
int buscar(clienteBanco **vector, int buscame, int tamvector)
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

    if (inicio > fin)
    {
        return -1;
    }

    else if ((listastruct[ptomedio]->nroCuenta) == buscame)
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

int main()
{

    FILE *transacciones = fopen("transacciones.txt", "r");

    int *cuentas = (int *)malloc(sizeof(int) * 2);
    int monto, pos;
    char operador;
    fscanf(transacciones, "%c", operador);

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
