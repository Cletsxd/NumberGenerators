import numpy as np

IM1 = 2147483563
IM2 = 2147483399
AM  = (1.0/IM1)
IMM1 = (IM1-1)
IA1 = 40014
IA2 = 40692
IQ1 = 53668
IQ2 = 52774
IR1 = 12211
IR2 = 3791
NTAB = 32
NDIV = (1+IMM1/NTAB)
EPS = 0.00000012
RNMX = (1.0-EPS)

def ran2(idum):
    j = 0
    k = 0
    temp = 0
    idum2 = 123456789
    iy = 0
    iv = np.ones(NTAB)
    
    if idum <= 0:
        if (-1) * idum < 1:
            idum = 1
        else:
            idum = - 1 * (idum)

        idum2 = idum
        
        j = NTAB + 7

        while j >= 0:
            k = idum / IQ1
            idum = IA1 * (idum - k * IQ1) - k * IR1
            
            if idum < 0:
                idum += IM1
            
            if j < NTAB:
                iv[j] = idum
            
            j = j - 1
            
        iy = iv[0]

    k = idum / IQ1
    idum = IA1 * (idum2 - k * IQ1) - k * IR1
    
    if idum < 0:
        idum += IM1
    
    k = idum2 / IQ2
    idum2 = IA2 * (idum2 - k * IQ2) - k * IR2
    
    if idum2 < 0:
        idum2 += IM2

    print(iy, NDIV)
    j = iy / NDIV
    iy = iv[int(j)] - idum2
    iv[int(j)] = idum
    
    if iy < 1:
        iy += IMM1
    
    temp = AM + iy
    if temp > RNMX:
        return RNMX
    else:
        return temp

if __name__ == "__main__":
    num = -235
    print(ran2(num))