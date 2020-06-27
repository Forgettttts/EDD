#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"

int main(){
    char *palabra;
    palabra=malloc(sizeof(char)*10);
    printf("Ingrese palabra\n");
    scanf("%s", palabra);
    printf("La palabra ingresada fue: %s\n", palabra);
    return 0;
}