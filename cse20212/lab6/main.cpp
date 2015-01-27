/*
	John F. Lake, Jr.  main.cpp
	Driver file - Tests the puzzle solving algorithm
*/


#include "Puzzle.h"
#include <iostream> 
#include <string>
using namespace std; 

int main(){
	
	//Make 3 puzzles - easy, medium, and hard, and solve them: 
	Puzzle myPuz1("easy.txt"); 
	cout << "Original Easy puzzle:"<<endl; 
	myPuz1.print(); 
	myPuz1.solve(); 
	cout << "Solved puzzle:"<<endl; 
	myPuz1.print(); 
	
	Puzzle myPuz2("medium.txt"); 
	cout << "Original medium puzzle:"<<endl; 
	myPuz2.print(); 
	myPuz2.solve(); 
	cout << "Solved puzzle:"<<endl; 
	myPuz2.print(); 
	
	Puzzle myPuz3("hard.txt"); 
	cout << "Original hard puzzle:"<<endl; 
	myPuz3.print(); 
	myPuz3.solve(); 
	cout << "Solved puzzle:"<<endl; 
	myPuz3.print(); 
	
	
	
}
