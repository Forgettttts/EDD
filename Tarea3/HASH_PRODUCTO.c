#define M 1000000 // Espacio en la Tabla para almacenar M ranuras
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


ranuraProducto HT[M]; // Se declara la tabla de hashing HT como un arreglo de ranuras de tamaño M.


int HashInsertProducto(ranuraProducto HT[], tipoClave K, producto I){

    int inicio, i;
    int pos = inicio = h(K); // inicio es r_{0} (r sub cero) en la formula de celdas alternativas. Aquí se genera la ranura 0

    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != K; i++) // Si la celda está ocupada y no es la clave que busco, este for me sirve para encontrar la ranura alternativa
    {
        pos = inicio + p(K, I) % M; // Proxima ranu4ra en la secuencia.
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

producto HashSearchProducto(ranuraProducto HT[], tipoClave K){
    int inicio, i;
    int pos = inicio = h(K); // inicio es r_{0} (r sub cero) en la formula de celdas alternativas. Aquí se genera la ranura 0

    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != K; i++) // Si la celda está ocupada y no es la clave que busco, este for me sirve para encontrar la ranura alternativa
    {
        pos = inicio + p(K, i) % M; // Proxima ranu4ra en la secuencia. Obesrbar que i es el número de intento de ranura (iteración)
    }

    if (HT[pos].clave == K){
        return HT[pos].info_producto;
    }
    else
    {
        return VALORINVALIDO;
    }
}