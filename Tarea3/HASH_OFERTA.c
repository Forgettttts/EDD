#define M 1000000// Espacio en la Tabla para almacenar M ranuras
#define VACIA -1 // Inicio mi tabla con -1 en todas las ranuras, lo que me indica que esa celda no ha sido usada

typedef int tipoClave; //vamos a definir las claves como nros enteros, (Para el problema, clave es codigo_producto)


typedef struct { // Definición de TIPO oferta
    tipoClave codigo_producto;
    int cantidad_descuento; // A partir de esta cantidad de unidades a comprar se hace un descuento
    int monto_descuento; // Monto en pesos a descontar dada la cantidad de productos del campo cantidad_productos
}oferta; // Las ofertas deben almacenarse en OTRO Hashing cerrado


typedef struct{ // Cada ranura contiene una clave y la información asociada
    tipoClave clave;
    oferta info_oferta;
}ranuraOferta; 


ranuraOferta HT[M]; // Se declara la tabla de hashing HT como un arreglo de ranuras de tamaño M.


//TODO Resolver el asunto de Factor de carga
//! a = N/M

int digitos_centrales(int num) { // Esta función retorna los dígitos centrales de un número, recordar que tiene que estár en relación con M (no sobrepasar)
    
}


int h(tipoClave K ){ // Método del cuadrado medio
    return digitos_centrales(K*K)+1;
}


int h2(tipoClave k) { // Esta función h2 es la que me permite usar el método de Hashing doble para resolución de colisiones
    
}


int p(tipoClave k, int i) { //Función p que me permite buscar ranuras alternativas frente a una colisión
    return i*h2(k);
}


int HashInsertOferta(ranuraOferta HT[], tipoClave K, oferta I){

    int inicio, i;
    int pos = inicio = h(K); // inicio es r_{0} (r sub cero) en la formula de celdas alternativas. Aquí se genera la ranura 0

    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != K; i++) // Si la celda está ocupada y no es la clave que busco, este for me sirve para encontrar la ranura alternativa
    {
        pos = inicio + p(K, i) % M; // Proxima ranu4ra en la secuencia.
    } // Obs: si llego a una celda vacía entonces inserto ahí (salí del for), si en cambio la clave es igual a la que busco, entonces no se puede insertar esa clave, ya que se repetiría
    
    if (HT[pos].clave == K){
        return 0; //* Inserción fallida, clave repetida
    }
    else{
        HT[pos].clave = K;
        HT[pos].info_oferta = I;
        return 1; //* El 1 = inserción exitosa
    }
}

oferta HashSearchOferta(ranuraOferta HT[], tipoClave K){
    int inicio, i;
    int pos = inicio = h(K); // inicio es r_{0} (r sub cero) en la formula de celdas alternativas. Aquí se genera la ranura 0

    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != K; i++) // Si la celda está ocupada y no es la clave que busco, este for me sirve para encontrar la ranura alternativa
    {
        pos = inicio + p(K, i) % M; // Proxima ranu4ra en la secuencia. Obesrbar que i es el número de intento de ranura (iteración)
    }

    if (HT[pos].clave == K){
        return HT[pos].info_oferta;
    }
    else
    {
        return VALORINVALIDO;
    }
}