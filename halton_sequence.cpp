#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float halton_sequence(long index, long base){
    float f = 1;
    float r = 0, aux = 0;

    while(index > 0){
        f = f / base;
        r = r + f * (index % base);
        aux = floor((index / base));
        index = aux;
    }

    return r;
}

int main(){
    long number = 34545, b = 6;

    printf("%f\n", halton_sequence(number, b));
}