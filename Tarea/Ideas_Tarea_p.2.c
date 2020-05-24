/*Lo que se podria hacer al comienzo del codigo, es declarar un struct tipo :*/

typedef struct punto
{
    int x;
    int y;
}Punto;


int main(){
    /*y al momento de hacer un while para poder leer el archivo y poder almacenarlo como structs por separados, sin 
    perder ninguno, podriamos hacer algo como:*/
    Punto lectura; //En este struct se guardara cada struct leido, es importante que dentro del while se guarde en otro struct, ya que si no lo hacemos, perderemos
    //               a todos los structs leidos, por que al guardarse todos los structs en este, se reescribira en la siguiente iteracion, perdiendo el anterior
    int num_struct=0; // Esto nos servira para ir nombrando los structs leidos, como para poder sabiendo cuantos structs fueron leidos
    while (fread(&lectura,sizeof( struct Punto),1,fp) == 1) { // Aqui no se si es que se refiere con ese 1 a que se leera 1 struct por cada iteracion o si es que 
    //                                                           en total en todo el archivo se leera tan solo 1 struct (mas facil si es que solo es el primer caso)
    char prefijo[15]; // Le daremos 15 por que el prefijo al ser el numero de struct, sabemos que hay un max de 10.000.000 cuentas, por lo que
    //                  podriamos llegar a una cuenta con ese numero como prefijo, ademas hay que sumarle el largo del resto del nombre mas el caracter de salida
    itoa(num_struct, prefijo, 10 ); // Aqui lo que se hace es pasar el num_struct (numero identificador del struct) a string, para poder
    //                                 definir un prefijo para el nombre, tipo 1struct, 2struct, etc.
    strcat(prefijo, "Punto");
    }
}
