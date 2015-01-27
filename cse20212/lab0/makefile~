all: main

main: main.o mortgage.o
	g++ main.o mortgage.o -o main
	
main.o: main.cpp
	g++ -c main.cpp
	
mortgage.o: mortgage.cpp
	g++ -c mortgage.cpp 
	
clean: 
	rm -f *.o main
