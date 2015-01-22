Last login: Thu Jan 22 12:08:20 on ttys000
Irinas-MacBook-Pro:~ irina$ ls
Applications		Downloads		Library			New Folder With Items	Public			VMMORPG
Desktop			Int_lesson		Movies			Pictures		PyUserInput		py.py
Documents		JuceMidi		Music			Project-X		PycharmProjects		pyrtmidi
Irinas-MacBook-Pro:~ irina$ cd /Users/irina/VMMORPG
Irinas-MacBook-Pro:VMMORPG irina$ ls
OpenGL			OpenGL.xcodeproj	chunk.VMC
Irinas-MacBook-Pro:VMMORPG irina$ OpenGL
-bash: OpenGL: command not found
Irinas-MacBook-Pro:VMMORPG irina$ cd /Users/irina/VMMORPG/OpenGL
Irinas-MacBook-Pro:OpenGL irina$ ls
client_connect.h	free_camera.h		main.cpp		models.h
Irinas-MacBook-Pro:OpenGL irina$ nano 1.py







































  GNU nano 2.0.6                                                 File: 1.py                                                                                                Modified  

f = open("chunk.VMC", "w+")
for i in range(16*16*16):
        if i%256 == 0:
                f.write('1')
        else:
                f.write('0')
f.close()                   










































^G Get Help                   ^O WriteOut                   ^R Read File                  ^Y Prev Page                  ^K Cut Text                   ^C Cur Pos
^X Exit                       ^J Justify                    ^W Where Is                   ^V Next Page                  ^U UnCut Text                 ^T To Spell
