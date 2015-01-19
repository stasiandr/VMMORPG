f = open("chunck.txt", "w+")
for i in range(256*16*16):
	f.write("1")
f.close()
