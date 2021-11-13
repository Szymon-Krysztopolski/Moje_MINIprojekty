import matplotlib.pyplot as plt
import numpy as np
from scipy import spatial

sun = [-100, -500, 1000]
v1 = 0.8
v2 = 0.2


def hsv2rgb(h, s, v):
    if (h == 360): h = 0
    if (s == 0):
        r = v
        g = v
        b = v
    else:
        H = int(h / 60)
        f = h / 60 - H
        p = v * (1 - s)
        q = v * (1 - (s * f))
        t = v * (1 - (s * (1 - f)))

        if (H == 0):
            r = v
            g = t
            b = p
        elif (H == 1):
            r = q
            g = v
            b = p
        elif (H == 2):
            r = p
            g = v
            b = t
        elif (H == 3):
            r = p
            g = q
            b = v
        elif (H == 4):
            r = t
            g = p
            b = v
        elif (H == 5):
            r = v
            g = p
            b = q
        else:
            r = 1
            g = 1
            b = 1
    return (r, g, b)


def gradient_hsv_gbr(v, a, b):
    h = 140 - v * 130
    return hsv2rgb(h, a, b)


def main():
    plt.figure(figsize=(10, 10))

    file = open("big.dem", "r")
    tab = file.readline().split()
    tab = list(map(int, tab))
    w, h, sbp = tab

    mapa = np.zeros((w, h))

    for i in range(h):
        line = file.readline().split()
        mapa[i] = list(map(float, line))
    file.close()

    mini = mapa.min()
    maxi = mapa.max()
    img = np.zeros((w, h, 3))

    for i in range(w):
        for j in range(h):
            v = 1
            s = 1
            ##simple shaders
            # if(j+1<h):
            #    if(mapa[i][j]<mapa[i][j+1]): v=v1
            if (i + 1 < w and j + 1 < h):
                a = np.array([i, j, mapa[i][j]])
                b = np.array([i + 1, j, mapa[i + 1][j]])
                c = np.array([i, j + 1, mapa[i][j + 1]])
                tmp = np.cross(a - b, a - c)
                sun_vec = sun - a

                cos = np.dot(sun_vec, tmp) / (np.linalg.norm(sun_vec) * np.linalg.norm(tmp))

            if (cos < 0):
                v = 1 + cos * v1
            else:
                v = 1 - cos * v2

            img[i][j] = gradient_hsv_gbr((mapa[i][j] / maxi), s, v)

    plt.imshow(img)
    plt.savefig('img.pdf')
    plt.show()

    plt.close()


if __name__ == '__main__':
    main()