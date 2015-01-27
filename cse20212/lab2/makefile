all: main Rational

main: main.o C4Col.o C4Board.o 
	g++ main.o C4Col.o C4Board.o -o main
	
Rational: Rational.o
	g++ Rational.o -o Rational
	
Rational.o: Rational.cpp
	g++ -c Rational.cpp
	
main.o: main.cpp
	g++ -c main.cpp
	
C4Col.o: C4Col.cpp
	g++ -c C4Col.cpp
C4Board.o:  C4Board.cpp
	g++ -c C4Board.cpp
	
clean: 
	rm -f *.o main Rational; 
