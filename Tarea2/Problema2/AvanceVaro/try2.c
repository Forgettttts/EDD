#include <stdlib.h>
#include <stdio.h>

int prueba(int* antecesor){
    if(*antecesor==1){
        printf("Se hace\n");
        *antecesor=2;
        return 0;
    }
    return 1;
}

int main(){
    int antecesor=1;
    printf("Inicialmente tiene un valor de %d\n", antecesor);
    if (prueba(&antecesor)==0){
        printf("Retorna, con un valor de %d\n", antecesor);
    }

    else if (prueba(&antecesor) == 1){
        printf("ERROR\n");
    }
    return 0;
}