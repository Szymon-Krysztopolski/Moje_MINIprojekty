import numpy as np
from matplotlib import pyplot as plt

def odl(x,y,z):
    if(x**2+y**2<z): return 1
    else: return 0

def main():
    n=100
    center=n/2
    r=np.array([20,35,50])
    borders=r*r

    R=np.full((n,n),0)
    G=np.full((n,n),0)
    B=np.full((n,n),0)
    mapa=np.array([R,G,B])

    for i in range(n):
        for j in range(n):
            for z,color in zip(borders,mapa):
                if(odl(center-i,center-j,z)):
                    color[i][j]=255
                    break
    plt.imshow(np.moveaxis(mapa, 0, 2))
    plt.savefig('okregi.pdf')
    plt.show()

if __name__ == '__main__':
    main()