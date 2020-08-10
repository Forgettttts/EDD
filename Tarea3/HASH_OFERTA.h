#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


int calcular_M_of(int N){ //Esta función calucla M de acuerdo a la cantidad N y a un factor de carga a tal que 0.6 < a < 0.7
    return (int)(N/0.7)+1;
}


void init_Tabla_Oferta(ranuraOferta* HT, int N){
    int M = calcular_M_of(N);
    HT = (ranuraOferta*)malloc(sizeof(ranuraOferta)*M);
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


int HashInsertOferta(ranuraOferta* HT, tipoClave K, oferta I, int M){

    int inicio, i;
    int pos = inicio = h(K, M); // inicio es r_{0} (r sub cero) en la formula de celdas alternativas. Aquí se genera la ranura 0

    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != K; i++) // Si la celda está ocupada y no es la clave que busco, este for me sirve para encontrar la ranura alternativa
    {
        pos = (inicio + p(K, i)) % M; // Proxima ranu4ra en la secuencia.
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

oferta HashSearchOferta(ranuraOferta* HT, tipoClave K, int M){
    int inicio, i;
    int pos = inicio = h(K, M); // inicio es r_{0} (r sub cero) en la formula de celdas alternativas. Aquí se genera la ranura 0

    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != K; i++) // Si la celda está ocupada y no es la clave que busco, este for me sirve para encontrar la ranura alternativa
    {
        pos = (inicio + p(K, i)) % M; // Proxima ranu4ra en la secuencia. Obesrbar que i es el número de intento de ranura (iteración)
    }

    if (HT[pos].clave == K){
        return HT[pos].info_oferta;
    }
    else
    {
        oferta VALORINVALIDO;
        VALORINVALIDO.codigo_producto=-10;
        VALORINVALIDO.cantidad_descuento = 0;
        VALORINVALIDO.monto_descuento = 0;
        return VALORINVALIDO;
    }
}