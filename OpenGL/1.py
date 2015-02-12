def ten(n):
    return '0'*(4-len(str(n)))+str(n)
print(ten(1))
h, d = map(int, input('Number of chunks: ').split())
a, b, c = map(int, input("Sizes of chunks: ").split())
for i in range(h):
    for j in range(d):
        o = open(str(i)+str(j)+'.VMC', 'w')
        o.write(ten(i)+ten(0)+ten(j))
        for x in range(a):
            for y in range(b):
                for z in range(c):
                    if y < 3 or (y == 6 and x == 2 and z == 3):
                        o.write('1')
                    else:
                        o.write('0')
        o.close()
