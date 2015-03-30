#encoding: utf-8
def ten(n):
    return '0'*(4-len(str(n)))+str(n)

from random import uniform
from random import random
def ver(pro):
    e = random()
    if e < pro:
        return True
    return False
def disc(x1, y1, x2, y2, points):
    if x1 < 0:
        x1 -= 1
    else:
        if x1 > len(points)-1:
            x1 += 1
        x1 %= len(points)
    if x2 < 0:
        x2 -= 1
    else:
        if x2 > len(points)-1:
            x2 += 1
        x2 %= len(points)
    if y1 < 0:
        y1 -= 1
    else:
        if y1 > len(points[0])-1:
            y1 += 1
        y1 %= len(points[0])
    if y2 < 0:
        y2 -= 1
    else:
        if y2 > len(points[0])-1:
            y2 += 1
        y2 %= len(points[0])
    return x1, y1, x2, y2
def square(x1, y1, x2, y2, r_c, points):
    xs = (x1+x2)//2
    ys = (y1+y2)//2
    x1, y1, x2, y2 = disc(x1, y1, x2, y2, points)
    points[xs][ys] = (points[x1][y1] + points[x1][y2] + points[x2][y1] + points[x2][y2] + uniform(-r_c, r_c))//4
def diamond(x1, y1, x2, y2, r_c, points):
    xs = (x1+x2)//2
    ys = (y1+y2)//2
    x1, y1, x2, y2 = disc(x1, y1, x2, y2, points)
    points[xs][ys] = (points[xs][y1] + points[xs][y2] + points[x1][ys] + points[x2][ys] + uniform(-r_c, r_c))//4
def sq_draw(level, r_c, points):
    if level > len(points) or level > len(points[0]):
        return
    lx = (len(points)-1)//level
    ly = (len(points[0])-1)//level
    for i in range(level):
        for j in range(level):
            square(lx*i, ly*j, lx*(i+1), ly*(j+1), r_c, points)
    for i in range(level):
        for j in range(level):
            x1, x2 = lx*i, lx*(i+1)
            y1, y2 = ly*j, ly*(j+1)
            sx = (x2 - x1)//2
            sy = (y2 - y1)//2
            diamond(x1, y1 - sy, x2, y1 + sy, r_c, points)
            diamond(x1 - sx, y1, x1 + sx, y2, r_c, points)
            diamond(x1, y2 - sy, x2, y2 + sy, r_c, points)
            diamond(x2 - sx, y1, x2 + sx, y2, r_c, points)
    r_c /= 1
    if d/level <= 64:
        r_c /= 1.1
    if d/level <= 32:
        r_c /= 1.5
    if d/level <= 16:
        r_c /= 2.5
    if d/level <= 8:
        r_c /= 20
    if d/level <= 4:
        r_c /= 200000000000
    if d/level <= 2:
        r_c /= 10000000000000000000000000000
    if d/level <= 1:
        r_c = 1000000000000000000000000000000000000000000
    sq_draw(level*2, r_c, points)

d = 512

bioms = [[0 for i in range(d+1)] for j in range(d+1)]
bioms[0][0] = 10
bioms[0][-1] = 10
bioms[-1][-1] = 100
bioms[-1][0] = 100
sq_draw(1, 1000000000000000, bioms)

for i in range(len(bioms)):
    for j in range(len(bioms[i])):
        if bioms[i][j] < 50:
            bioms[i][j] = 1
        else:
            bioms[i][j] = 0

#print("bioms generated")
e = open("bioms.lcp", "w")
for i in bioms:
    for j in i:
        print(int(j), end = ' ', file = e)
    print(file = e)
e.close()
#print("bioms saved")

points = [[0 for i in range(d+1)] for j in range(d+1)]
points[0][0] = 100
points[0][-1] = 100
points[-1][-1] = 100
points[-1][0] = 100
sq_draw(1, 10, points)

#print("generated")
e = open("landscape.lcp", "w")
for i in points:
    for j in i:
        print(int(j), end = ' ', file = e)
    print(file = e)
e.close()
#print("saved")
#generation - end

templates = []
def build_template(x, y, z, field, templatepath, i):
    if len(templates) <= i:
        t = open(templatepath, 'r')
        header = t.read(6)
        wid = (ord(header[0])-1)*256 + ord(header[1])-1
        hei = (ord(header[2])-1)*256 + ord(header[3])-1
        dee = (ord(header[4])-1)*256 + ord(header[5])-1
        temp = [[[0 for k in range(dee)] for j in range(hei)] for i in range(wid)]
        for i in range(wid):
            for j in range(hei):
                for k in range(dee):
                    temp[i][j][k] = t.read(1)
        t.close()
        templates.append(temp)
    else:
        temp = templates[i]
    
    #cx = x//a
    #cy = y//b
    #cz = z//c
    #bx = x%cx
    #by = y%cy
    #bz = z%cz
    #o = open(str(cx)+str(cy)+str(cz)+'.VMC', 'w')
    #o.write(ten(cx)+ten(cy)+ten(cz))
    #o.close()    
    for i in range(len(temp)):
        for j in range(len(temp[i])):
            for k in range(len(temp[i][j])):
                if temp[i][j][k] != '-':
                    field[x + i][y + j][z + k] = temp[i][j][k]
    del temp

#ach, bch, cch = map(int, input('Number of chunks: ').split())
#a, b, c = map(int, input("Sizes of chunks: ").split())
ach, bch, cch = 10, 10, 10
a, b, c = 16, 16, 16
blocks = [[['0' for i in range(a*ach)] for j in range(b*bch)] for k in range(c*cch)]
for x_c in range(a*ach):
    for y_c in range(b*bch):
        for z_c in range(c*cch):
            if y_c < points[x_c][z_c]:
                if bioms[x_c][z_c] == 0:
                    blocks[x_c][y_c][z_c] = '1'
                elif bioms[x_c][z_c] == 1:
                    blocks[x_c][y_c][z_c] = '7'
                else:
                    blocks[x_c][y_c][z_c] = '0'
build_template(10, points[10][10], 10, blocks, 'temp.template', 0)
print('template builded')
for i in range(ach):
    for j in range(bch):
        for k in range(cch):
            #print(str(i)+str(j)+str(k)+'.VMC opened')
            o = open(str(i)+str(j)+str(k)+'.VMC', 'w')
            o.write(ten(i)+ten(j)+ten(k))
            for x in range(a):
                for y in range(b):
                    for z in range(c):
                        x_c = x + i*a
                        y_c = y + j*b
                        z_c = z + k*c
                        o.write(blocks[x_c][y_c][z_c])
            o.close()
print('chunked')
