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

ach, bch, cch = map(int, input('Number of chunks: ').split())
a, b, c = map(int, input("Sizes of chunks: ").split())

iss = [[["" for i in range(cch)] for j in range(bch)] for i in range(ach)]
ids = [[["" for i in range(cch)] for j in range(bch)] for i in range(ach)]
for i in range(ach):
    for j in range(bch):
        for k in range(cch):
            o = open(str(i)+str(j)+str(k)+'.VMC')
            ids[i][j][k] = o.read(12)            
            iss[i][j][k] = o.read()
            o.close()
field = [[[False for i in range(c*cch)] for j in range(b*bch)] for k in range(a*ach)]
for chunk_x in range(len(iss)):
    for chunk_y in range(len(iss[chunk_x])):
        for chunk_z in range(len(iss[chunk_x][chunk_y])):
            for i in range(len(iss[chunk_x][chunk_y][chunk_z])):
                x = i // (b*c)
                y = (i-x*b*c) // c
                z = (i-x*b*c - y*c) % c
                t = iss[chunk_x][chunk_y][chunk_z][x*b*c + y*c + z]
                if t == 0:
                    field[x][y][z] = False
                else:
                    field[x][y][z] = True


an, yan = map(float, input('angles: ').split())
radian = 57.295779513
#an /= radian
#yan /= radian
x, y, z = map(float, input('position: ').split())

print(cos(an), sin(an), cos(yan), sin(yan))
for i in range(6):
    x0 = int(x) + 1
    y0 = int(y) + 1
    z0 = int(z) + 1
    r1 = x0 / cos(an) / cos(yan)
    r2 = y0 / sin(yan)
    r3 = z0 / sin(an) / cos(yan)
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
                rx = xb + int(x)
                ry = yb + int(y)
                rz = zb + int(z)
                print('answer', rx, ry, rz)
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
                rx = xb + int(x)
                ry = yb + int(y)
                rz = zb + int(z)
                print('answer', rx, ry, rz)
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
                rx = xb + int(x)
                ry = yb + int(y)
                rz = zb + int(z)
                print('answer', rx, ry, rz)
                field[xb][yb][zb] = 0
                break
        elif xb >= len(field) and yb >= len(field[0]) and zb >= len(field[0][0]):
            break        
    x = x0
    y = y0
    z = z0
