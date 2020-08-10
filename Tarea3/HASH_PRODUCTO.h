#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VACIA -1 // Inicio mi tabla con -1 en todas las ranuras, lo que me indica que esa celda no ha sido usada

typedef int tipoClave; //vamos a definir las claves como nros enteros, (Para el problema, clave es codigo_producto)


typedef struct { // Definición del TIPO producto en venta
    tipoClave codigo_producto;
    char nombre_producto[31];
    int precio;
}producto; // Los productos deben almacenarse en un HASHING CERRADO


typedef struct{ // Cada ranura contiene una clave y la información asociada
    tipoClave clave;
    producto info_producto;
}ranuraProducto; 


int calcular_M_prod(int N){ //Esta función calucla M de acuerdo a la cantidad N y a un factor de carga a tal que 0.6 < a < 0.7
    return (int)(N/0.7)+1;
}


void init_Tabla_Productos(ranuraProducto* HT, int N){
    int M = calcular_M_prod(N);
    HT = (ranuraProducto*)malloc(sizeof(ranuraProducto)*M);
}


//TODO: No sé si debemos pedir/liberar memoria por cada ranura de la tabla, o liberar HT nomás. Modificar en caso de error.
void delete_Tabla(ranuraOferta* HT){
    free(HT);
}

int digitos_centrales(int num) { // Esta función retorna los dígitos centrales de un número, recordar que tiene que estár en relación con M (no sobrepasar)
    //* Primero calculamos el largo de un numero
    int largo, numero = num;
    if (numero > 0){
        for (largo = 0; numero > 0; largo++){
            numero = numero / 10;
        }
    }
    //* El largo esta guardado en la variable: largo
    // Los numeros centrales serán el mismo número excluyendo el dígito inicial y el dígito final
    int numeros_centrales = (num / 10) - (num / (int)(pow(10, (largo - 1))) * ((int)(pow(10, (largo - 2)))));
    return numeros_centrales;
}


int h(tipoClave K, int M){ // Método del cuadrado medio
    int largo, numero = K*K;
    if (numero > 0){ //Calculo el largo de la clave al cuadrado
        for (largo = 0; numero > 0; largo++){
            numero = numero / 10;
        }
    }
    if (largo <= 2)
    {
        return (K*K)%M;
    }
    else
    {
        return (digitos_centrales(K*K)) % M;
    }
    
}


int h2(tipoClave k, int i) { // Esta función h2 es la que me permite usar el método de Hashing doble para resolución de colisiones
    return (7*i*i)+(3*i)+1;
}


int p(tipoClave k, int i) { //Función p que me permite buscar ranuras alternativas frente a una colisión
    return i*h2(k, i);
}


int HashInsertProducto(ranuraProducto* HT, tipoClave K, producto I, int M){

    int inicio, i;
    int pos = inicio = h(K, M); // inicio es r_{0} (r sub cero) en la formula de celdas alternativas. Aquí se genera la ranura 0

    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != K; i++) // Si la celda está ocupada y no es la clave que busco, este for me sirve para encontrar la ranura alternativa
    {
        pos = inicio + p(K, i) % M; // Proxima ranu4ra en la secuencia.
    } // Obs: si llego a una celda vacía entonces inserto ahí (salí del for), si en cambio la clave es igual a la que busco, entonces no se puede insertar esa clave, ya que se repetiría
    
    if (HT[pos].clave == K){
        return 0; //* Inserción fallida, clave repetida
    }
    else{
        HT[pos].clave = K;
        HT[pos].info_producto = I;
        return 1; //* El 1 = inserción exitosa
    }
}


producto HashSearchProducto(ranuraProducto* HT, tipoClave K, int M){
    int inicio, i;
    int pos = inicio = h(K, M); // inicio es r_{0} (r sub cero) en la formula de celdas alternativas. Aquí se genera la ranura 0

    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != K; i++) // Si la celda está ocupada y no es la clave que busco, este for me sirve para encontrar la ranura alternativa
    {
        pos = inicio + p(K, i) % M; // Proxima ranu4ra en la secuencia. Obesrbar que i es el número de intento de ranura (iteración)
    }

    if (HT[pos].clave == K){
        return HT[pos].info_producto;
    }
    else
    {
        producto VALORINVALIDO;
        VALORINVALIDO.codigo_producto=-10;
        strcpy(VALORINVALIDO.nombre_producto, "Producto invalido");
        VALORINVALIDO.precio = 0;
        return VALORINVALIDO;
    }
}