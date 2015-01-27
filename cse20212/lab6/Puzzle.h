/*
	John F. Lake, Jr.  Puzzle.h 
	Interface/Implementation for the puzzle class - no templating done for this lab. 
*/

#ifndef PUZZLE_H
#define PUZZLE_H
#include <fstream> 		//Used for file I/O
#include <sstream>		//Used to parse lines for input
#include <iterator>		//Used for printing
#include <string>		
#include <cstdlib>		
#include <iostream> 		//Simple I/O
#include <vector> 		//Contains Puzzle info
#include <cmath>		//Used for sqrt
using namespace std; 


class Puzzle{
	public: 
		Puzzle(string="puzzle1.txt"); 	//Default constructor
		void getInfo(string); 		//Gets the file for the puzzle object
		void print(); 			//Prints the puzzle line by line
		int isValid(int,int,int);	//Checks if a certain move is valid
		int checkSquare(int,int,int); 	//Checks if a move violates any number in the mini-square it resides in
		int checkRow(int,int); 		//Checks if the same number is in the row
		int checkColumn(int,int); 	//Checks if the same number is in the column
		void placeNumber(int,int,int); 	//Places the number in the square provided.  Calls isValid(). 
		int isSolved();			//Checks if the board is completed.
		void solve(); 			//Solves the puzzle. 
		void update3DVec(); 		//Updates which numbers different spaces can have.  
	private: 
		vector< vector<int> > board; 
		vector< vector < vector<int> > > possMoves; 
		string puzzle_file;  
};




//Constructor . 
Puzzle::Puzzle(string f){
	puzzle_file = f; 
	getInfo(puzzle_file);
	
	
	//sets the 3D vector so that every space can have all possible moves (to start out with.)
	for(int i=0;i<board[0].size();i++){
		vector< vector<int> > row;
		for(int j = 0;j<board[0].size();j++){
			vector<int> types; 
			for(int k = 0;k<board[0].size();k++){
				types.push_back(1); 
			}
			row.push_back(types); 
		}
		possMoves.push_back(row); 
		
	}
}


//Specific method for handling integer inputs
void Puzzle::getInfo(string file){
	string line;  					//line is used with sstream to parse for input on each line. 
	ifstream myFile; 				//input file stream 
	myFile.open(file.c_str(), ifstream::in); 	//Open the file					
	if (myFile.is_open()){				//If the file opens properly
		while(getline(myFile,line)){		//While there is another line to grab, get it, and parse it. 
			vector<int> thisLine;  
			int n; 			
			istringstream iss(line); 	
			while(iss >> n){
				thisLine.push_back(n); 	//Push back the inputs to the vector thisLine
			}	
			board.push_back(thisLine); 	//Push back the line into the 2D board vector.  
		}
		myFile.close();				//Close the file/ 
	}
	else{
		cout << "Error: File did not open properly."<<endl; //Print error message if file doesn't open.
	}
}


//Same concept as above- for int inputs.  
void Puzzle::print(){  
	//Cycle through line by line, and then value by value
	for(vector< vector<int> >::iterator outer = board.begin(); outer != board.end(); outer++){
		vector<int> currentLine = *outer; 
		for(vector<int>::iterator inner = currentLine.begin(); inner != currentLine.end(); inner++){
			cout << *inner; 
		}
		cout << endl; 
	}
	cout << endl; 
}


//Checks to see if input val is valid in row r. 
int Puzzle :: checkRow(int r, int val){
	for (int i = 0; i< board[r].size();i++){	   //Cycle through the row, from 0 to size-1. 
		if (board[r][i] == val){		   //If there is another input that is the same, return false. 
			return 0; 
		}
	}			
	return 1; 					//Otherwise, return true. 
}


//Checks to see if input val is valid in column c.
int Puzzle :: checkColumn(int c,int val){
	for (int i = 0; i< board[0].size();i++){	//Cycle through the column, from 0 to size-1
		if (board[i][c] == val){		//If another input is the same on the column, return false. 
			return 0; 
		}
	}
	return 1; 					//Otherwise, return true.  
}


//Checks to see if input val is valid in the mini square r,c resides in: 
int Puzzle :: checkSquare(int r, int c, int val){
	int sqSize = sqrt(board[0].size());     //3 for a 9x9, 2 for a 4x4, etc
	int startC = sqSize * (c / sqSize); 	//c and r divided by the sqSize times sqSize will give the mini square start point
	int startR = sqSize * (r / sqSize); 	//This start point, for a 9x9 square, would be 0, 3, or 6.   (4x4: 0,2)
	
	for(int i = startR;i< startR + sqSize;i++){ 		
		for(int j = startC; j < startC+sqSize;j++){
			if(board[i][j] == val) return 0; 		//If there's another value that is the same, return false. 
		}
	}
	return 1; 	//Otherwise, return 0.  
}



//Checks if a space or value is valid as an entry: 
int Puzzle::isValid(int row, int col, int val){
	if((row > board[0].size()-1) || (col > board[0].size()-1)) return 0;  //If a place is outside of the board, it's not valid
	if((val > board[0].size()) || (val<0)) return 0; 		 	//If a value is inappropriate, return 0 

	if(board[row][col] == 0){ //If there is nothing in the spot, then a number can be placed: 
		if(!(checkRow(row,val))) return 0; 			//Checks if the value is in the row
		if(!(checkColumn(col,val))) return 0;  		//Checks the column
		if(!(checkSquare(row,col,val))) return 0;	//Checks the square. 
	}
	else{
		return 0; 	//If there's already a number in the spot, return 0
	}
 
	return 1; 
}





//Easily place a number in any spot (r,c)
void Puzzle:: placeNumber(int r, int c, int val){
	if (isValid(r,c,val)){
		board[r][c] = val; 
	}else {
		cout << "Invalid entry."<<endl; 
	
	}
}



//If none of the spaces are zero, then it is a finished game.  
int Puzzle :: isSolved(){
	for (int i=0;i<board[0].size();i++){
		for(int j = 0;j<board[0].size();j++){
			if (board[i][j]==0) return 0; 
		}
	}
	return 1; 
}

/*
Void function which solves the puzzle (for ints)

This function cycles from the top left part of the puzzle, and checks
each and every spot for all possible values.  If there is only one possible 
value for a spot, the function inserts that value and continues until 
all of the spots are correctly filled in.  


If there are multiple possible values, it checks all of the open spots in the row and column.  
If none of those spots have the same possible value, it is safe to insert the number. 
*/
void Puzzle :: solve(){
	int currentRow=0,currentColumn=0,possValues,val;  //variables containing the row & column you are at, and the number of possible values there
	
	update3DVec(); //Update the possible values in the 3D vector.  
	while(!(isSolved())){ //While the puzzle is not solved, keep going. 
		possValues=0;
		for(int i = 0;i<board[0].size();i++){  			//For all possible values in the board
			if(possMoves[currentRow][currentColumn][i]==1){	//If the value is a valid move, increment possValues
				possValues++; 
				val = i+1; 
			}
		}
		
		
		if(possValues==1) { //If there's one possible value for a spot, insert it. 
			placeNumber(currentRow,currentColumn, val);
			update3DVec();
		}
		else{  //multiple possible values: 
		
		
			//Check accross row,column for same values.  If they aren't in  any other space, insert the number.
		
		
			//Checking the row for other spaces with the same possible value: 
			for(int i = 0; i< board[0].size();i++){ //values to check
				int sameVal = 0; 
				if(possMoves[currentRow][currentColumn][i]==1){ //If a value is valid at the given space, check the row:  
						for(int c = 0;c<board[0].size();c++){ //move across the row
							if(possMoves[currentRow][c][i]==1) sameVal++;  //If a space has a valid move i, add to sameVal
						}
						if(sameVal==1){	//if sameVal==1, there is only one space in the row that can have an input i.  
							 placeNumber(currentRow,currentColumn,i+1);  //place the number (i+1 because inputs are 1-9)
							update3DVec(); //Update possible values
						}
				}	
			}
			
			//Same thing with columns: 
			for(int i = 0; i< board[0].size();i++){ //values to check
				int sameVal = 0; 
				if(possMoves[currentRow][currentColumn][i]==1){ //If a value is valid at the given space, check the column: 
						for(int r = 0;r<board[0].size();r++){ //move across the column
							if(possMoves[r][currentColumn][i]==1) sameVal++; 
						}
						if(sameVal==1){
							 placeNumber(currentRow,currentColumn,i+1); 
							update3DVec();
						}
				}	
			}
		}
	
	
		//Change the space to check: 
		currentColumn++; //Move right along the row
		if(currentColumn >= board[0].size()){ //If you were in the last column: 
			currentColumn = 0; 				//Set the column to zero and increase the row
			currentRow++; 
			if(currentRow>=board[0].size()) currentRow=0; 	//if you were at the last row, set the row to zero (start at top right again)
		}
	}
}



//Function which updates the 3D vector holding information about possible values. 
void Puzzle::update3DVec(){
	for(int i = 0;i<board[0].size();i++){  //row
		for(int j = 0;j<board[0].size();j++){ //column
			for(int k = 0;k<board[0].size();k++){  //possible values
				if(!(isValid(i,j,k+1))){   	//if a value isn't valid, set that spot to zero.  
					possMoves[i][j][k]=0;
				}
			}
		}	
	}
}
#endif

