
virtmem: page_table.o main.o disk.o program.o
	gcc -DDEBUG page_table.o main.o disk.o program.o -o virtmem

page_table.o: page_table.c
	gcc -Wall -g -c page_table.c -o page_table.o

main.o: main.c
	gcc -Wall -g -c main.c -o main.o

disk.o: disk.c
	gcc -Wall -g -c disk.c -o disk.o

program.o: program.c
	gcc -Wall -g -c program.c -o program.o


clean:
	rm -f *.o virtmem
