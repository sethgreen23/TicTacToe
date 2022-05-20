morpion.exe: morpion.o
	gcc morpion.o -o morpion.exe

morpion.o: morpion.c
	gcc -c morpion.c

