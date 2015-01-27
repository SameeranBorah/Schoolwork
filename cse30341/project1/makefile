all: copyit

copyit: copyit.o
	gcc -DDEBUG -g -Wall copyit.o -o copyit
	rm -rf *.o
copyit.o: copyit.c
	gcc -c copyit.c
clean:
	rm -rf copyit
