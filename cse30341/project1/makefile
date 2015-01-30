all: copyit copyit_extracredit

copyit: copyit.o
	gcc -DDEBUG -g -Wall copyit.o -o copyit
	rm -rf *.o
copyit_extracredit: copyit_extracredit.o
	gcc -DDEBUG -g -Wall copyit_extracredit.o -o copyit_extracredit
	rm -rf *.o
copyit.o: copyit.c
	gcc -c copyit.c
copyit_extracredit.o: copyit_extracredit.c
	gcc -c copyit_extracredit.c
clean:
	rm -rf copyit
