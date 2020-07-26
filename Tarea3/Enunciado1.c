//TODO Dado que la cantidad de productos es grande, se pide usar HASHING CERRADO PARA ALMACENARLOS
// El programa debe:
//TODO: 1).- lEER UN CONJUNTO DE COMPRAS REALIZADAS POR CLIENTES
//TODO: 2).- MANTENER UN REGISTRO D ELAS VENTAS DE CADA PRODUCTO Y EL MONTO TOTAL OBTENIDO PRODUCTO DE ESTAS
//TODO: 3).- GENERAR UN RANKIN DE LOS PRODUCTOS CON MAYOR MONTO TOTAL OBTENIDO. Para la generación del ranking se debe usar un heap

//!Problemas a resolver en el TDA HASH (tanto producto como oferta):
//TODO: 1).- Debemos LEER de los archivos input la cantidad de elementos que pueden insertarse en la tabla de HASH, y a partir de eso generar un M que cumpla con la regla de factor de carga a = 0.7 (Hasta ahora M está definido arbitrariamente con #define)
//TODO: 2).- Aarreglar el VALORINVALIDO para los casos en que se necesite
//TODO: 3).- Definir una función h2 adecuada. Asegurarse de que retorne valores menores a M
//TODO: 4).- Implementar un heap

//*OBSERVACIONES:
// 1).- La cantidad de elementos que contendrá cada Hashing, se indica en la primera línea de cada archivo binario. (productos.dat y ofertas.dat)
// 2).- R (cantidad de productos en el ranking) es máximo 1.000.000
// 3).- N (cantidad de clientes a atender) es máximo 100.000
// 4).- C (cantidad de productos a comprar por un cliente) es máximo 1.000.000


//* AQUÍ EN ADELANTE INTENTO RESOLVER EL TEMA DE OBTENER LOS DÍGITOS CENTRALES DE UN NÚMERO, AVERIGUANDO PRIMERO LA CANTIDAD DE DÍGITOS
//* Útil para el método de cuadrado medio


void enteroacadena(int k, char* string); // Convertir un numero entero a cadena con objetivo de recorrer el string contando sus caracteres
// Esto nos permitiría saber a priori cuántos dígitos tiene un número

int main(){

    int k = 3567;
    char string[8];
    enteroacadena(k, string);
    printf("%s", string);
    
    return 0;
}

void enteroacadena(int k, char* string){
    sprintf(string, "%d", k);
}

/*
Lo otro que se puede hacer es esto:
El número 4578:
Código:
4578 % 10 = 8
4578 / 10 = 457     457 % 10 = 7
457  / 10 = 45       45 % 10 = 5
45   / 10 = 4         4 % 10 = 4

Pero se necesitaría saber de antemano cuántos dígitos tiene el número
*/