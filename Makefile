all : dsFile.o dsMain.o dsNode.o dsShell.o
	gcc -o main dsFile.o dsMain.o dsNode.o dsShell.o
	rm -f *.o

dsFile.o : 
	gcc -c Src/dsFile.c
dsMain.o : 
	gcc -c Src/dsMain.c
dsNode.o : 
	gcc -c Src/dsNode.c
dsShell.o : 
	gcc -c Src/dsShell.c