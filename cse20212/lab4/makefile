all: DeckTest MonkeySort Blackjack

DeckTest: DeckTest.o CardDeck.o 
	g++ DeckTest.o CardDeck.o -o DeckTest
MonkeySort: MonkeySort.o CardDeck.o
	g++ MonkeySort.o CardDeck.o -o MonkeySort
Blackjack: CardDeck.o Blackjack.o
	g++ Blackjack.o CardDeck.o -o Blackjack
Blackjack.o: Blackjack.cpp
	g++ -c Blackjack.cpp
MonkeySort.o: MonkeySort.cpp
	g++ -c MonkeySort.cpp
DeckTest.o: DeckTest.cpp
	g++ -c DeckTest.cpp
CardDeck.o: CardDeck.cpp
	g++ -c CardDeck.cpp

clean: 
	rm -f *.o DeckTest; 
	



