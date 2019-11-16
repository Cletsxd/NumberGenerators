#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

// Reference: https://www.cec.uchile.cl/cinetica/pcordero/MC_libros/NumericalRecipesinC.pdf (buscar: p. 306)
float ran2(long *idum){
    long j;
    long k;
    static long idum2 = 123456789;
    static long iy = 0;
    static long iv[NTAB];
    float temp;

    if(*idum <= 0){
        if(- (*idum) < 1){
            *idum = 1;
        }else{
            *idum = - (*idum);
        }

        idum2 = (*idum);

        for(j = NTAB + 7; j >= 0; j--){
            k = (*idum) / IQ1;
            *idum = IA1 * (*idum - k * IQ1) - k * IR1;

            if(*idum < 0){
                *idum += IM1;
            }

            if(j < NTAB){
                iv[j] = *idum;
            }

            iy = iv[0];
        }
    }

    k = (*idum) / IQ1;
    *idum = IA1 * (*idum - k * IQ1) - k * IR1;

    if(*idum < 0){
        *idum += IM1;
    }

    k = idum2 / IQ2;
    idum2 = IA2 * (idum2 - k * IQ2) - k * IR2;

    if(idum2 < 0){
        idum2 += IM2;
    }

    j = iy/NDIV;
    iy = iv[j] - idum2;
    iv[j] = *idum;

    if(iy < 1){
        iy += IMM1;
    }

    if((temp = AM * iy) > RNMX){
        return RNMX;
    }else{
        return temp;
    }
}

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
    long ncx = -235;
    long nhx = -235, b = 7;

    long ncy = -15900;
    long nhy = -15900;

    float cx, cy, hx, hy;

    long nauxx = -235, nauxy = -15900;

    FILE *file_pointer;
    file_pointer = fopen("data.csv", "w");

    for(int i = 0; i < 10000; i++){
        cx = ran2(&ncx);
        cy = ran2(&ncy);

        hx = halton_sequence(-1 * nhx, b);
        hy = halton_sequence(-1 * nhy, b);
        
        printf("CongX: %f, CongY: %f, HaltonX: %f, HaltonY: %f, X: %ld, Y: %ld\n", cx, cy, hx, hy, nauxx, nauxy);
        fprintf(file_pointer, "%f, %f, %f, %f\n", cx, cy, hx, hy);

        nauxy -= 1;
        nauxx -= 1;

        ncx = nhx = nauxx;
        ncy = nhy = nauxy;
    }
}