import math as mt

def halton_secuence(index, base):
    f = 1
    r = 0
    aux = 0

    while index > 0:
        f = f / base
        r = r + f * (index % base)
        aux = mt.floor(index / base)
        index = aux

    return r

if __name__ == '__main__':
    print(halton_secuence(234, 7))