/*
	John F. Lake, Jr.  main.cpp
	Driver file - tests inputs of ints and chars, and then plays a game.  
*/


#include "Puzzle.h"
#include <iostream> 
#include <string>
using namespace std; 

int main(){
	
	//Tests different types of puzzles: 
	cout << endl << endl << "PUZZLE INPUT TEST:"<<endl;
	Puzzle<int> puz1("puzzle1.txt");   //4x4 int puzzle
	Puzzle<int> puz2("puzzle2.txt");   //9x9 int puzzle
	Puzzle<char> puz3("puzzle3.txt");  //4x4 char puzzle (not necessarily a valid puzzle - just tests for char input.  
	
	cout << "4x4 int puzzle:"<<endl;
	puz1.print(); 
	cout << "9x9 int puzzle:"<<endl;
	puz2.print(); 
	cout << "4x4 char puzzle:"<<endl;
	puz3.print(); 
	
	
	//Game Simulations for 4x4 and 9x9 games: 
	
	int r, c, v; 
	cout << endl<<endl<<"4x4 GAME SIMULATION:"<<endl; 
	while(!(puz1.isSolved())){
		puz1.print();
		cout << "Enter a row, a column, and a value, starting from 0, separated by spaces."<<endl; 
		cin >> r >> c >> v;  //Get user input
		puz1.placeNumber(r,c,v); 
	}
	cout << "You finished the puzzle!"<<endl; 
	puz1.print(); 
	
	
	
	cout << endl<<endl<<"9x9 GAME SIMULATION:"<<endl; 
	while(!(puz2.isSolved())){
		puz2.print();
		cout << "Enter a row, a column, and a value, separated by spaces."<<endl; 
		cin >> r >> c >> v;  //Get user input
		puz2.placeNumber(r,c,v); 
	}
	cout << "You finished the puzzle!"<<endl; 
	puz2.print(); 
	
	
	
}
