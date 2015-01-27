/*
	John F. Lake, Jr.  DeckTest.cpp
	Tests the CardDeck class. 
*/
#include <iostream>
#include "CardDeck.h"
using namespace std; 

int main(){
	//First part (Just prints the results from shuffling): 
	CardDeck myDeck(31); //Make a CardDeck object with 10 cards
	cout << myDeck;      //Print the card deck
	myDeck.shuffle();    //Shuffle it
	cout << endl<< "After Shuffle:"<<endl<<myDeck; //Print the new order of the deck

}
