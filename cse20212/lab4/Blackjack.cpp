/*
	John F. Lake, Jr.  Blackjack.cpp
	Class which plays blackjack using the CardDeck class
*/

#include "CardDeck.h"  //CardDeck class
#include <iostream>    //Output to the user
using namespace std; 

//Returns the card value for the integers 0-12
int getValue(int v){
	switch(v){
		//Numbered cards:
		case 0:
		case 1: 
		case 2: 
		case 3: 
		case 4: 
		case 5: 
		case 6: 
		case 7: 
		case 8: 
			return v+2;   //The 0th card is 2, the 1st is 3, etc. 
			break; 
		//Face cards: 
		case 9: 
		case 10: 
		case 11: 
			return 10;   //Face cards have a value of 10. 
			break; 
		//Ace: 
		case 12: 
			return 11;  //An ace is worth 11. 
			break; 
	}
}



int main(){

	//Initialize variables
	int gameLoop = 1,handOver;  	//Variable used to keep the game going. 
	int playerValue;		//The value of the player's hand
	int dealerValue;		//The value of the dealer's hand
	int playerWins=0; 		//# of wins the player has
	int dealerWins=0;		//# of wins the dealer has
	CardDeck * deck;   		//Deck object uses pointers so that a new deck can be assigned in the loop. 
	deck = new CardDeck;  		//Standard deck of 52 cards.  
	(*deck).shuffle(); 		//Shuffle the deck so it's ready to play. 
	
	cout << "Welcome to blackjack!"<<endl<<endl; //Welcome message

	//Main loop for the game of blackjack.  The user can select 0 for hit, and 1 for stand
	while(gameLoop){
		cout << endl<<"New Hand:"<<endl;
		
		//Initial values for the player and the dealer: 
		handOver = 0; 
		playerValue = 0; 
		dealerValue = 0; 
		int input,temp = getValue((*deck).deal() % 13);  //13 values: 2,3,4,5,6,7,8,9,10,J(10),Q(10),K(10), and A(11)
		playerValue+= temp; 
		temp = getValue((*deck).deal() % 13) ; 
		dealerValue+= temp; 
		
		
		//Player's move to hit/stand: 
		cout << "Your hand: "<<playerValue<<"."<<endl;
		while(!handOver){ //while the hand is not over (while the user is still hitting: 
			cout << "Hit (1) or Stand (2)?"<<endl; 
			cin >> input; 				//Get input on whether to hit or stand

			if(input==1){ //Hit
				temp = getValue((*deck).deal() % 13); 
				if((*deck).getSize()<15){
					 deck = new CardDeck; //If there are fewer than 15 cards, set the deck pointer to a new deck object. 
					  (*deck).shuffle();
				}
				playerValue+= temp; 
			} 
			else if (input == 2){ //Stand:
				handOver = 1;   //The hand is over because the user is standing
			}
			else { cout << "Enter a valid input!" <<endl;}  //Correct the user for incorrect input
			
			cout << "Your hand: "<<playerValue<<"."<<endl;
			if(playerValue > 21){ //If the player busts, take appropriate action: 
				handOver = 1; 
				dealerWins++; 
				cout << "BUST!!!  Dealer wins!"<<endl; 
			}
		}
		cout <<endl; 
		
		//If player's hand is under 21 when they stop, the dealer goes until the hand is above 17. 
		if(playerValue < 22){
			while(dealerValue<17){ //While the dealer's hand is under 17
				cout << "Dealer's hand: "<<dealerValue<< ".  Your hand: "<<playerValue<<"."<<endl;  //Print the values of both hands
				temp = getValue((*deck).deal() % 13); 						  
				if((*deck).getSize()<15){
					 deck = new CardDeck; //If there are fewer than 15 cards, set the deck pointer to a new deck object. 
					 (*deck).shuffle(); 
				}
				dealerValue+= temp; 
			}
			cout << "Dealer's hand: "<<dealerValue<< ".  Your hand: "<<playerValue<<"."<<endl; 
			
			if(dealerValue > 21){ //Dealer busts (you win):
				cout << "Dealer busts! You win!"<<endl; 
				playerWins++; 
			}	
			else if(playerValue > dealerValue){ //You win: 
				cout << "You win!"<<endl; 
				playerWins++; 
			}
			else if (dealerValue > playerValue){ //You lose: 
				cout << "Dealer wins!"<<endl; 
				dealerWins++; 
			}
			else{cout <<"Push!"<<endl;} //if playerValue==dealerValue, it's a push.  
		}
		
		//Ask user if they want to play again or not.  
		cout << "Would you like to play again?  (1 for yes, 0 for no.)"<<endl; 
		cin>>input; 
		if(!input) gameLoop = 0;
	}
	//Print the number of wins for each player 
	cout << "The player had "<<playerWins << " wins and the dealer had " << dealerWins<< " wins!"<<endl<<endl; 
}
