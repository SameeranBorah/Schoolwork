all: mandel mandelmovie mandelMultiThread

mandel: mandel.o bitmap.o
	gcc mandel.o bitmap.o -o mandel -lpthread
mandelMultiThread: mandelMultiThread.o bitmap.o
	gcc mandelMultiThread.o bitmap.o -o mandelMultiThread -lpthread
mandelmovie: mandelmovie.o
	gcc mandelmovie.o -o mandelmovie

mandelmovie.o: mandelmovie.c
	gcc -Wall -g -c mandelmovie.c -o mandelmovie.o

mandel.o: mandel.c
	gcc -Wall -g -c mandel.c -o mandel.o
mandelMultiThread.o: mandelMultiThread.c
	gcc -Wall -g -c mandelMultiThread.c -o mandelMultiThread.o

bitmap.o: bitmap.c
	gcc -Wall -g -c bitmap.c -o bitmap.o

clean:
	rm -f mandel.o bitmap.o mandel
