/*Problema 2:

Los clientes de un banco estan guardados en el siguiente struct:

typedef struct {
    int nroCuenta; //? Entre 1 y 10.000.000 (no siempre consecutivos)
    int saldo;
    char nbre[51];
    char direccion[51];
} clienteBanco;

~Funcion:
    //TODO: actualizarSaldos(char *clientes, char *transacciones)
    de donde:
        -char* clientes= //*string, representa el nombre de un archivo binario, el cual contiene una cantidad desconocida de structs del tipo
//*                        clienteBanco. Los structs estan ordenado de forma creciente por el nroCuenta 
        -char* transacciones= //*string, representa el noombre de un archivo en formato ASCII, el cual contiene las transacciones de los clientes
//*                              Cada linea es una transaccion, con el formato de:
            + C N: //? A la cuenta C, se le depositan N pesos
            - C N: //? Desde la cuenta C, salen N pesos
            > C1 C2 N: //? La cuenta C1, le transfiere N pesos a la cuenta C2

            //! EL FIN DEL ARCHIVO ES DADO POR EOF
~Invocar funcion actualizarSaldos:
    Los parámetros a usar para la función actualizarSaldos serán indicados a través de la línea de comando, como parámetros de la función main.
    El obejtivo de la funcion es actualizar el archivo de clientes.

    Suponiendo que el ejecutable para su programa es tarea1-parte2, un ejemplo de línea de comando es:

    //TODO:  ./tarea1-parte2 clientes.dat transacciones.txt
    //! Los nombres de los archivos pueden variar, deben aceptar cualquier nombre
*/