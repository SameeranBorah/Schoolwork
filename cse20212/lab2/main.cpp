/*
	John Lake main.cpp
	Driver program for connect four. 
*/

#include "C4Board.h"
#include <iostream>
using namespace std; 


int main(){
	int playAgain = 1;  //playAgain is used to determine whether or not to run the game again
	while(playAgain){ //Loop that allows the player to play again. 
		C4Board c4; 
		c4.play(); 
		cout << "Would you like to play again? (1 for yes, 0 for no.)" << endl; 
		cin >> playAgain;  //If they enter 0, the loop will end and the program will end as well. 
	}
}
