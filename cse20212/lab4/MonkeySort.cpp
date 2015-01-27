/*
	John F. Lake, Jr.  MonkeySort.cpp
	Counts the number of shuffles until a deck is sorted. 
*/
#include <iostream>
#include "CardDeck.h"
using namespace std; 

void mSort(CardDeck d){
	int numShuffles;  //Number of shuffles made 	  
	while(!d.inOrder()){  //While the deck isn't ordered, shuffle it and increment numShuffles
		d.shuffle(); 
		numShuffles++; 
	}
	cout << "It took " << numShuffles << " shuffles to sort this " << d.getSize() << " card deck."<<endl;  //Print result to user
}


int main(){
	//Initialize card decks of 7, 8, and 9 cards
	CardDeck mySevenDeck(7);
	CardDeck myEightDeck(8); 
	CardDeck myNineDeck(9);  
	
	//Sorting the 7 card deck 3 times: 
	for(int i = 0;i<3;i++){
		mySevenDeck.shuffle(); //Shuffle the deck to get it out of order. 
		mSort(mySevenDeck); 
	}
	
	//Sorting the 8 card deck 3 times: 
	for(int i = 0;i<3;i++){
		myEightDeck.shuffle(); //Shuffle the deck to get it out of order. 
		mSort(myEightDeck); 
	}
	
	//Sorting the 9 card deck 3 times: 
	for(int i = 0;i<3;i++){
		myNineDeck.shuffle(); //Shuffle the deck to get it out of order. 
		mSort(myNineDeck); 
	}
	
	

}


