all: myshell
	rm -rf *.o

myshell: myshell.o
	gcc myshell.o -DDEBUG -o myshell
myshell.o: myshell.c
	gcc -c myshell.c
clean:
	rm -rf myshell 
