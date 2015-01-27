/*
	John Lake C4Board.h
	Interface for the board class. 
*/
#ifndef C4BOARD_H
#define C4BOARD_H
#include "C4Col.h"
#include <ostream>
using namespace std; 
 
class C4Board{

	friend ostream &operator<<(ostream &, const C4Board &); 

	public: 
		C4Board(); //Default constructor
		void display(); //Will print the board to the user in simple text. 
		void play(); //Allows 2 players to play the game. 
	private: 
		int numCols; //Number of columns
		C4Col Board[7]; //Column objects. 	
		int gameOver();  //returns 0 if not over, 1 if player 1 wins, and 2 if player 2 wins.  
		void compTurn(); //Used to have a computer play against the user	
};
#endif
