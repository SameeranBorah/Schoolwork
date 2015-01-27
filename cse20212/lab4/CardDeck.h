/*
	John F. Lake, Jr.   CardDeck.h
	Interface for the CardDeck class - stores a deck of cards as an STL deque of n integers
*/

#ifndef CARDDECK_H
#define CARDDECK_H

#include <deque> 
#include <ostream> 
using namespace std; 

class CardDeck{
	//Overloaded << operator
	friend ostream& operator<<(ostream& , CardDeck &);
		
	public: 
		CardDeck(int=52); //Default value is 52 cards 
		int getSize(); //Returns the size of the deck.
		void shuffle(); //Shuffles the deck. /private:
		int inOrder();  //Returns 1 if the deck is in increasing order; 0 otherwise. 
		int deal();  //Returns a card from the deck.  The card is removed from the deck.  
	
	private: 
		deque<int> deck; //Double ended queue that holds the cards. 	
};

#endif
