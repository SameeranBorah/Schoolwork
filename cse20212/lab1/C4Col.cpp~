/*
	John Lake  C4Col.cpp
	This is the implementation for the C4Col class
*/
#include "C4Col.h" 
#include <iostream> 
using namespace std; 

//Default Constructor
C4Col::C4Col(){
	numDiscs = 0; //0 discs in a column to begin with.
	maxDiscs = 6; //6 rows
	Discs = new char[maxDiscs];
	for(int i=0;i<6;i++){ //Set column so that no player has a piece anywhere on the board. 
		Discs[i]=' '; 
	}
}
//Deconstructor
C4Col::~C4Col(){
	delete[] Discs; 
}

//Determines whether or not the column is full
int C4Col::isFull(){
	if(numDiscs == maxDiscs) return 1; 
	return 0; //If it isn't full, it will return false.
}
//Returns the disc at the specified point
char C4Col::getDisc(int n){
	if(n>maxDiscs-1){cout << "Invalid input: there are only " << maxDiscs << " rows."<<endl;}
	else{
		return Discs[n]; 
	}
}
//Returns the maximum number of discs that can fit in a column (# of rows)
int C4Col::getMaxDiscs(){
	return maxDiscs; 
}
//Add a disc
int C4Col::addDisc(char c){
	if(isFull()){ cout << "The column is full!" << endl; } //if the column is full, do not add to it. 
	else{
		Discs[numDiscs++] = c;  //Add the specified character (X or O) to the specified location, and incrememnt the number of Dics.
	}
}
