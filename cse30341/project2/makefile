all: myshell myshell_extracredit
	rm -rf *.o
myshell: myshell.o
	gcc myshell.o -g -Wall -DDEBUG -o myshell
myshell.o: myshell.c
	gcc -c -g myshell.c
myshell_extracredit: myshell_extracredit.o
	gcc myshell_extracredit.o -g -Wall -DDEBUG -o myshell_extracredit
myshell_extracredit.o: myshell_extracredit.c
	gcc -c -g myshell_extracredit.c
clean:
	rm -rf myshell myshell_extracredit
