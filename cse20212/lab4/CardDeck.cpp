/*
	John F. Lake, Jr.  CardDeck.cpp
	Implementation for the CardDeck class.  
*/


#include "CardDeck.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <deque>
#include <iterator>
#include <ctime>
#include <ostream> 

using namespace std; 

//Constructor
CardDeck::CardDeck(int n){
	for(int i=0;i<n;i++) deck.push_back(i+1); 
	srand(time(NULL)); 
}

//GetSize method; returns the size of the card deck. 
int CardDeck::getSize(){
	return deck.size(); 
}

//Shuffles the deck. 
void CardDeck::shuffle(){
	random_shuffle(deck.begin(),deck.end()); 
}

//Checks if the deck is in increasing order. 
int CardDeck::inOrder(){
	int biggest = getSize();   			//Variable to check if the deck is in order. 
	deque<int>::const_reverse_iterator i; 		//Reverse iterator object
	for( i = deck.rbegin(); i != deck.rend(); ++i){ //Iterate backwards through the deck
		if(*i < biggest) return 0; 		//If the current spot (*i) is smaller than variable "biggest", the deck is unordered.  
		biggest--; 
	}
	return 1; 					//If the "biggest" variable is always greater than or equal to *i, it is ordered. 
}

//Returns the card to the user, and removes it from the deck.  
int CardDeck::deal(){
	int r = rand() % getSize(); //Random number from 0 to deckSize-1
	deck.erase(deck.begin()+r); //Remove that number from the deck
	return r+1;  //Return the number to the user.  r+1 is because r is the location, not the number of the card (deck[0] is card # 1)
}


//Overloaded << operator
ostream& operator<<(ostream & out, CardDeck & d){
	out << "Deck:"<<endl; 
	deque<int>::const_iterator i; //iterator for the deck
	for(i=d.deck.begin(); i != d.deck.end(); ++i){
		 //Print the contents of the deck, each separated with a comma. 
		 out << *i;
		 if(d.deck.end() != i+1){  
			out <<",";
		 }
		 else{
		 
		 }
		 out << endl;  
	}
	return out; 
} 
