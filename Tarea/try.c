#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct punto
{
    int x;
    int y;
} p;

int main(){
    p.x=1;
    p.y=3;
    p.x = 5;
    p.y = 10000000;
    char perro[8];
    itoa(p.y, perro, 10);
    printf("%s\n", perro);

    return 0;
}