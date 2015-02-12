all: myshell
	rm -rf *.o

myshell: myshell.o
	gcc myshell.o -g -Wall -DDEBUG -o myshell
myshell.o: myshell.c
	gcc -c -g myshell.c
clean:
	rm -rf myshell 
