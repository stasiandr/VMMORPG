def ten(n):
    return '0'*(4-len(str(n)))+str(n)
#ach, bch, cch = map(int, input('Number of chunks: ').split())
#a, b, c = map(int, input("Sizes of chunks: ").split())
ach, bch, cch = 4, 4, 4
a, b, c = 6, 6, 6
for i in range(ach):
    for j in range(bch):
        for k in range(cch):
            o = open(str(i)+str(j)+str(k)+'.VMC', 'w')
            o.write(ten(i)+ten(j)+ten(k))
            #print(str(i)+str(j)+str(k)+'.VMC')
            for x in range(a):
                for y in range(b):
                    for z in range(c):
                        x_c = x + i*a
                        y_c = y + j*b
                        z_c = z + k*c
                        xx = a*ach # узкость лодки
                        yy = b*bch
                        zz = c*cch # длина лодки
                        if (x_c < 4 and y_c < 4-x_c and y_c < 4 and y_c > 2-x_c and z_c > 2 - y_c and z_c < y_c + zz - 3): # одни трибуны
                            o.write('1')
                        elif (x_c > xx-10 and y_c < x_c-xx+5 and y_c < 4 and y_c > x_c-xx+3 and z_c > 2 - y_c and z_c < y_c + zz - 3): # трибуны напротив
                            o.write('1')
                        elif (z_c < 4 and y_c < 4-z_c and y_c > 2-z_c and x_c > 3 - y_c and x_c < y_c + xx - 4): # другие трибуны
                            o.write('1')
                        elif (z_c > zz-10 and y_c < z_c-19 and y_c > z_c-21 and x_c > 3 - y_c and x_c < y_c + xx - 4): # другие трибуны напротив
                            o.write('1')
                        elif (y_c == 0 and x_c > 3 and x_c < xx-4 and z_c > 3 and z_c < zz-4): # другие трибуны напротив
                            o.write('1')
                        #elif (x_c == 5 and z_c == 10 and y_c < yy-2): # мачта
                        #    o.write('1')
                        #elif (x_c == 5 and y_c > 5 and z_c > y_c/2 - 1.5 and z_c < zz - y_c/2 - 2.5): # парус
                        #    o.write('1')
                        #elif (y_c == yy-1 and x_c > 3 and x_c < 7 and z_c > 8 and z_c < 12 and not (x_c == 5 and z_c == 10)): # смотровая площадка
                        #    o.write('1')
                        else:
                            o.write('0')
            o.close()
