#include <stdio.h>
#include <string.h>
int main(){
    int hora[]=23:59;
    char momento[3];
    printf("Ingrese la hora actual en formato 24[hrs]: \n");
    scanf("%d",hora);
    
    int horario=((hora[0]*10)+hora[1]);

    printf("Hora= %d\n", hora);
    /*
    if (horario>12){
        strcpy(momento, "PM");
        horario-=12;
    }
    else if (horario == 0){
        horario = 12;
        strcpy(momento, "AM");
    }
    else{
        strcpy(momento, "AM");
    }
    int minutos = ((hora[3] * 10) + hora[4]);
    printf("Mins= %d\n", minutos);
    int hora_12[]={horario, ":", minutos};
    printf("la hora en formato 12 hrs es: %d\n", hora_12);
    */
    return 0;
}