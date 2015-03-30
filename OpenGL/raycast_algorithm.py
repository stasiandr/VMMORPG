def mprint(f):
    for i in f:
        for j in i:
            print(j, end = ' ')
        print()
def m3print(f):
    for i in f:
        mprint(i)
        print()
from math import *

#ach, bch, cch = map(int, input('Number of chunks: ').split())
#a, b, c = map(int, input("Sizes of chunks: ").split())
ach, bch, cch = 6, 6, 6
a, b, c = 10, 10, 10

iss = [[["" for i in range(cch)] for j in range(bch)] for i in range(ach)]
ids = [[["" for i in range(cch)] for j in range(bch)] for i in range(ach)]
for i in range(ach):
    for j in range(bch):
        for k in range(cch):
            o = open(str(i)+str(j)+str(k)+'.VMC')
            ids[i][j][k] = o.read(12)
            iss[i][j][k] = o.read()
            o.close()
field = [[[0 for i in range(c*cch)] for j in range(b*bch)] for k in range(a*ach)]
for chunk_x in range(ach):
    for chunk_y in range(bch):
        for chunk_z in range(cch):
            for i in range(a*b*c):
                x = i // (b*c)
                y = (i-x*b*c) // c
                z = (i-x*b*c - y*c) % c
                t = iss[chunk_x][chunk_y][chunk_z][x*b*c + y*c + z]
                x += chunk_x * a
                y += chunk_y * b
                z += chunk_z * c
                if t == '0':
                    field[x][y][z] = 0
                else:
                    field[x][y][z] = 1

'''while True:
    slic = int(input())
    for i in range(len(field)):
        for j in range(len(field)):
            for k in range(len(field)):
                if j == slic:
                    print(field[i][j][k], end = ' ')
        print()'''

an, yan = map(float, input('angles: ').split())
radian = 57.295779513
an /= radian
yan /= radian
resx, resy, resz = map(float, input('position: ').split())
x, y, z = resx, resy, resz

print(cos(an), sin(an), cos(yan), sin(yan))
for i in range(8):
    if (an >= 0/radian and an < 90/radian):
        x0 = x + 1
        z0 = z + 1
    if (an >= 90/radian and an < 180/radian):
        x0 = x - 1
        z0 = z + 1
    elif (an >= 180/radian and an < 270/radian):
        x0 = x - 1
        z0 = z - 1
    elif (an >= 270/radian and an < 360/radian):
        x0 = x + 1
        z0 = z - 1
    if (yan >= -90/radian and yan < 0/radian):
        y0 = y - 1
    elif (yan >= 0/radian and yan <= 90/radian):
        y0 = y + 1
    
    r1 = abs(x0 / cos(an) / cos(yan))
    r2 = abs(y0 / sin(yan))
    r3 = abs(z0 / sin(an) / cos(yan))
    print(i, x, y, z)
    if r1 < r2 and r1 < r3:
        y0 = r1 * sin(yan)
        z0 = r1 * cos(yan) * cos(an)
        print(x0, y0, z0)
        xb = int(x0)
        yb = int(y0)
        zb = int(z0)
        print(xb, yb, zb)
        if xb < len(field) and yb < len(field[0]) and zb < len(field[0][0]):
            if field[xb][yb][zb] == 1:
                print('answer', xb, yb, zb)
                rx = xb + resx
                ry = yb + resy
                rz = zb + resz
                print('answer', rx, ry, rz)
                print(field[xb][yb][zb])
                field[xb][yb][zb] = 0
                break
        elif xb >= len(field) and yb >= len(field[0]) and zb >= len(field[0][0]):
            break
    elif r2 < r3:
        x0 = r2 * cos(yan) * cos(an)
        z0 = r2 * cos(yan) * sin(an)
        print(x0, y0, z0)
        xb = int(x0)
        yb = int(y0)
        zb = int(z0)
        print(xb, yb, zb)
        if xb < len(field) and yb < len(field[0]) and zb < len(field[0][0]):
            if field[xb][yb][zb] == 1:
                print('answer', xb, yb, zb)
                rx = xb + resx
                ry = yb + resy
                rz = zb + resz
                print('answer', rx, ry, rz)
                print(field[xb][yb][zb])
                field[xb][yb][zb] = 0
                break
        elif xb >= len(field) and yb >= len(field[0]) and zb >= len(field[0][0]):
            break
    else:
        x0 = r3 * cos(yan) * cos(an)
        y0 = r3 * sin(yan)
        print(x0, y0, z0)
        xb = int(x0)
        yb = int(y0)
        zb = int(z0)
        print(xb, yb, zb)
        if xb < len(field) and yb < len(field[0]) and zb < len(field[0][0]):
            if field[xb][yb][zb] == 1:
                print('answer', xb, yb, zb)
                rx = xb + resx
                ry = yb + resy
                rz = zb + resz
                rz = zb + int(z)
                print('answer', rx, ry, rz)
                print(field[xb][yb][zb])
                field[xb][yb][zb] = 0
                break
        elif xb >= len(field) and yb >= len(field[0]) and zb >= len(field[0][0]):
            break
    x = x0
    y = y0
    z = z0
