//John F. Lake, Jr.  othello.c 
//Prompts user with the size of the board, and constructs a game of othello for the user. 
//Player 1 is white; 2 is red. 

//Necessary imports: 
#include <stdio.h> 
#include "gfx.h" 
#include <math.h> 



//Size is a global variable. 
int size; 


//Function Prototypes: 
int validMove(int row, int column, int cells[size][size]); 
void updatePositions(float cellSize, int cells[size][size]); 
void clearBoard(void); 
void drawBoard(int totalSize, int cellSize); 
void drawPiece(int color, int row, int column, float cellSize); 
void drawCircle(float x, float y, float r); 
int checkUp(int turn, int row, int column, float cellSize, int cells[size][size]);
int checkDown(int turn, int row, int column, float cellSize, int cells[size][size]);
int checkRight(int turn, int row, int column, float cellSize, int cells[size][size]);
int checkLeft(int turn, int row, int column, float cellSize, int cells[size][size]);
int checkUR(int turn, int row, int column, float cellSize, int cells[size][size]); 
int checkDR(int turn, int row, int column, float cellSize, int cells[size][size]);
int checkUL(int turn, int row, int column, float cellSize, int cells[size][size]);
int checkDL(int turn, int row, int column, float cellSize, int cells[size][size]);




//Main Method/Function
int main(void){
	
	//Get the size of the board from the user, and declare necessary variables: 
	printf("Enter the size of the board.\n"); 
	scanf("%d",&size); 
	float width = 500; 
	float height = 500; 
	float cellSize = width/size; 
	int turn = 1; //The turn of the current player
	int stillGoing = 1; //Flag to check in the while loop

	//Used to see what player occupies each cell:  //For size=10, the starting cells will be [4][4],[4,5],[5,4],[5,5]
	int cells[size][size]; 
	int i; 
	int j; 
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			cells[i][j] = 0; 
		}
	}

	//Put the starting circles in the center of the board (or close to it if the size is odd) 
	cells[size/2][size/2] =1; 
	cells[size/2-1][size/2] =2; 
	cells[size/2][size/2-1] =2; 
	cells[size/2-1][size/2-1] =1; 
	

	//Open the window: 
	gfx_open(width,height,"Othello"); 
	drawBoard(width,cellSize); 
	updatePositions(cellSize,cells); 

	//While loop that continues while the game is being played: 
	while(stillGoing){
	
		//Used to calculate if the spaces are all filled up yet:
		int spacesFilled=0;
		int p1Total=0; 
		int p2Total=0;  
	
		//If the user presses 'q', quit the program: 
		char c = gfx_wait(); 
       		switch(c){
         		case 'q': 
        	            stillGoing = 0; 
        	            break;
		}


		//Location of Last Click
		int row = ((int)gfx_ypos())/((int) cellSize); 
                int column = ((int)gfx_xpos())/((int) cellSize); 
	
		//Clear, update, and draw the board and circles: 
	       	clearBoard(); 
		drawBoard(width, cellSize); 
		updatePositions(cellSize,cells); 


		//If the move the player makes is valid (if the space is adjacent to a previous move), draw the circle and update the board: 
		if(validMove(row,column,cells)){
			switch(turn){
				case 1: 	
					turn = 2; 
					drawPiece(1,row, column, cellSize); 
					cells[row][column] = 1; 
					checkRight(1,row,column,cellSize,cells);
					checkLeft(1,row,column,cellSize,cells);
					checkUp(1,row,column,cellSize,cells);
					checkDown(1,row,column,cellSize,cells);
					checkUL(1,row,column,cellSize,cells);
					checkUR(1,row,column,cellSize,cells);
					checkDL(1,row,column,cellSize,cells);
					checkDR(1,row,column,cellSize,cells);
					break; 
				case 2: 
					turn = 1; 
					drawPiece(0,row, column, cellSize); 
					cells[row][column] = 2; 
					checkRight(2,row,column,cellSize,cells);
					checkLeft(2,row,column,cellSize,cells);
					checkUp(2,row,column,cellSize,cells);
					checkDown(2,row,column,cellSize,cells);
					checkUL(2,row,column,cellSize,cells);
					checkUR(2,row,column,cellSize,cells);
					checkDL(2,row,column,cellSize,cells);
					checkDR(2,row,column,cellSize,cells);
					break; 
			}
		}
		//Update the positions for the current turn: 
		updatePositions(cellSize,cells); 
	

	//Check to see if the board is full yet: 
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(cells[i][j])spacesFilled++;  //Increase the number of cells with values other than 0. 
			if(cells[i][j] == 1)p1Total++;  //Increase the count of white cells. 
			if(cells[i][j] == 2)p2Total++;  //Increase the count of red cells. 
		}
	}

	//If all of the spaces are filled, the game is over: 
	if(spacesFilled==(size*size)){  
		stillGoing = 0;  //End the loop 
	
		//Player 1 Wins: 
		if(p1Total>p2Total){
			printf("Player 1 (White) wins with %d spaces filled!\n",p1Total); 
		}
		//Player 2 Wins: 
		else if(p2Total>p1Total){
			printf("Player 2 (Red) wins with %d spaces filled!\n",p2Total);
		}
		//Tie:	
		else{
			printf("There was a tie; each player had %d spaces filled!\n",p1Total);
		}
	}   
     }
}

//Functions!:

//Draws The Pieces at every location: 
/** 
*@return void 
*@param cellSize The width and height of each cell. 
*@param cells The cell matrix that keeps track of each cell. 
*/ 
void updatePositions(float cellSize, int cells[size][size]){
	int i; //Row
	int j; //Column

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){

			//At each cell, check if it has the value of player 1 or 2, and draw the piece at the cell accordingly. 
			//If no player has entered a piece in the cell, nothing will happen to it. 
			if(cells[i][j] == 1){
				drawPiece(1,i,j,cellSize); 
			}else if (cells[i][j] == 2){
				drawPiece(0,i,j,cellSize); 
			}		

		}
	}
}




//Checks to see if the current move is adjacent to any of the previous occupied cells. 
/**
*@return int 
*@param row The row of the cell being checked
*@param column The column of the cell being checked 
*@param cells The cell matrix being used to keep track of which value is in each cell. 
*/
int validMove(int row, int column,int cells[size][size]){
	//If the row or column are outside of the bounds of the board, it's definitely not a valid move: 
	if(row>size-1 || row<0 || column>size-1 || column<0){  
		return 0; 
	}
	//Also, if a player has already placed a piece in the cell, it is not valid; you cannot play over a piece: 
	else if(cells[row][column]) {
		return 0; 
	}

	int i; //Row 
	int j; //Column

	
	//Used to determine the bounds for the for loop: 
	int rowLowerBound; 
	int rowUpperBound; 
	int colLowerBound; 
	int colUpperBound; 
	

	//If the cell is at the border, adjust the bounds accordingly to avoid an index out of bounds error: 
	if(row == 0){ 
		rowLowerBound = 0; 
		rowUpperBound = row+1;
	}else if(row == size-1){
		rowLowerBound = row-1; 
		rowUpperBound = size-1; 		
	}else{
		rowLowerBound = row-1; 
		rowUpperBound = row+1; 	
	}

	if(column == 0){ 
		colLowerBound = 0; 
		colUpperBound = column+1;
	}else if(column == size-1){
		colLowerBound = column-1; 
		colUpperBound = size-1; 		
	}else{
		colLowerBound = column-1; 
		colUpperBound = column+1; 	
	}
	for(i=rowLowerBound;i<=rowUpperBound;i++){
		for(j=colLowerBound;j<=colUpperBound;j++){
			if(cells[i][j]) return 1; 
		}
	}
	return 0; 	
}



//Clears the Screen.  Essentially just a renamed "gfx_clear()" call to make the code easier to read in the main function. 
void clearBoard(void){
     gfx_clear(); 
}




/**
*@return void
*@param totalSize Total width and height of the board 
*@param cellSize Width and height of each cell 
*/
void drawBoard(int totalSize, int cellSize){
	     gfx_color(255,255,255); //Color it white: 
	
	     float width = totalSize*cellSize; 
	     float height = totalSize*cellSize; 

	     //Draw Exterior Border
	     gfx_line(0,0,width,0); 
	     gfx_line(0,0,0,height); 
	     gfx_line(0,height, width, height); 
	     gfx_line(width, 0, width, height); 


	     int i; //Row
	     int j; //Column
	     
	     //Draw Rows and Columns: 
	     for(i=0;i<height;i+=cellSize){
		 gfx_line(i,0,i,totalSize); 
	     }


	     for(j=0;j<height;j+=cellSize){
		  gfx_line(0,j,totalSize,j); 
	     } 
	     gfx_flush(); 
}






/** 
*@return void 
*@param color Flag for determining color; white if true, red if false. 
*@param row Row of the piece 
*@param column Column of the piece 
*@param cellSize Width and Height of each cell
*/
void drawPiece(int color, int row, int column, float cellSize){
         //Colors can be white or Red: 
         if(color){
               gfx_color(255,255,255);
         }else {gfx_color(255,0,0);}

         float xPosition = (cellSize*column)+(cellSize/2); 
         float yPosition = (cellSize*row)+(cellSize/2);
         float radius  = (cellSize/2); 

         drawCircle(xPosition,yPosition,radius); 
}







/**@return void 
*@param x X location 
*@param y Y location
*@param r Radius
*/
void drawCircle(float x, float y, float r){
     float angle; 
     for(angle = 0; angle< M_PI*2;angle+=0.01){
          gfx_line(x,y,x+(r*cos(angle)),y+(r*-sin(angle))); 
     }
     gfx_flush(); 
}



//CHANGE THESE TO BE ONE FUNCTION USED EXTENSIVELY (parameter specifying direction, up, down, etc. 


//Check Up for spaces to change:
/**
*@return int 
*@param turn The turn of the current player.
*@param row The row of the cell the player clicked. 
*@param column The column of the cell the player clicked. 
*@param cellSize The size of the cell the player clicked. 
*@param cells The matrix of cells to keep track of where each player has gone. 
*/
int checkUp(int turn, int row, int column, float cellSize, int cells[size][size]){
	
	int i=row; //Row check iteration variable
	int j=column; //Column Check iteration variable; 
	while(cells[i][j]){
		if(i>size-1 || i<0 || j>size-1 || j<0)break; 	
		
			
		if(cells[i][j] == cells[row][column]){
			int a = row; 
			int b = column; 
			while(a>=i){
				if(a>size-1 || a<0 || b>size-1 || b<0)break; 
				
				switch(turn){
						case 1: 	
							drawPiece(1,a, b, cellSize); 
							cells[a][b] = 1; 
							break; 
						case 2: 
							drawPiece(0,a, b, cellSize); 
							cells[a][b] = 2; 
							break; 
					}	
		
				a--; 
			}	
		}
		i--; 
	}
	return 0; 
}





//Check Down for spaces to change:
/**
*@return int 
*@param turn The turn of the current player.
*@param row The row of the cell the player clicked. 
*@param column The column of the cell the player clicked. 
*@param cellSize The size of the cell the player clicked. 
*@param cells The matrix of cells to keep track of where each player has gone. 
*/
int checkDown(int turn, int row, int column, float cellSize, int cells[size][size]){	
	
	int i=row; //Row check iteration variable
	int j=column; //Column Check iteration variable; 
	while(cells[i][j]){
		if(i>size-1 || i<0 || j>size-1 || j<0)break; 
		if(cells[i][j] == cells[row][column]){
			int a = row; 
			int b = column; 
			while(a<=i){
				if(a>size-1 || a<0 || b>size-1 || b<0)break; 
				switch(turn){
						case 1: 	
							drawPiece(1,a, b, cellSize); 
							cells[a][b] = 1; 
							break; 
						case 2: 
							drawPiece(0,a, b, cellSize); 
							cells[a][b] = 2; 
							break; 
					}	
		
				a++; 
			}	
		}
		i++;
	}
	return 0; 
}




//Check right for spaces to change:
/**
*@return int 
*@param turn The turn of the current player.
*@param row The row of the cell the player clicked. 
*@param column The column of the cell the player clicked. 
*@param cellSize The size of the cell the player clicked. 
*@param cells The matrix of cells to keep track of where each player has gone. 
*/
int checkRight(int turn, int row, int column, float cellSize, int cells[size][size]){
	
	int i=row; //Row check iteration variable
	int j=column; //Column Check iteration variable; 
	while(cells[i][j]){
		if(i>size-1 || i<0 || j>size-1 || j<0)break; 
		
		if(cells[i][j] == cells[row][column]){
			int a = row; 
			int b = column; 
			while(b<=j){
				if(a>size-1 || a<0 || b>size-1 || b<0)break; 
				switch(turn){
						case 1: 	
							drawPiece(1,a, b, cellSize); 
							cells[a][b] = 1; 
							break; 
						case 2: 
							drawPiece(0,a, b, cellSize); 
							cells[a][b] = 2; 
							break; 
					}	
		
				b++; 
			}	
		}
		j++; 
	}
	
	return 0; 
}
//Check Left for spaces to change:
/**
*@return int 
*@param turn The turn of the current player.
*@param row The row of the cell the player clicked. 
*@param column The column of the cell the player clicked. 
*@param cellSize The size of the cell the player clicked. 
*@param cells The matrix of cells to keep track of where each player has gone. 
*/
int checkLeft(int turn, int row, int column, float cellSize, int cells[size][size]){
	
	int i=row; //Row check iteration variable
	int j=column; //Column Check iteration variable; 


	//While the cells are occupied: 
	while(cells[i][j]){
		//If the cell is outside of the board, exit. 
		if(i>size-1 || i<0 || j>size-1 || j<0)break; 

		
		//If the cell at i,j contains the same color as the current position, fill in all of the spaces between with the color at i,j:
		if(cells[i][j] == cells[row][column]){
			int a = row; 
			int b = column; 
			while(b>=j){
				if(a>size-1 || a<0 || b>size-1 || b<0)break; 
	
				switch(turn){
						case 1: 	
							drawPiece(1,a, b, cellSize); 
							cells[a][b] = 1; 
							break; 
						case 2: 
							drawPiece(0,a, b, cellSize); 
							cells[a][b] = 2; 
							break; 
					}	
		
				b--; 
			}	
		}
		j--; 
		 
	} 
	return 0; 
}
//Check Diagonally Up and Right for spaces to change:
/**
*@return int 
*@param turn The turn of the current player.
*@param row The row of the cell the player clicked. 
*@param column The column of the cell the player clicked. 
*@param cellSize The size of the cell the player clicked. 
*@param cells The matrix of cells to keep track of where each player has gone. 
*/
int checkUR(int turn, int row, int column, float cellSize, int cells[size][size]){
 
	
	int i=row; //Row check iteration variable
	int j=column; //Column Check iteration variable; 
	while(cells[i][j]){
		if(i>size-1 || i<0 || j>size-1 || j<0)break; 
		 	
		if(cells[i][j] == cells[row][column]){
			int a = row; 
			int b = column; 
			while(b<=j && a>=i){
				if(a>size-1 || a<0 || b>size-1 || b<0)break; 
			
				switch(turn){
						case 1: 	
							drawPiece(1,a, b, cellSize); 
							cells[a][b] = 1; 
							break; 
						case 2: 
							drawPiece(0,a, b, cellSize); 
							cells[a][b] = 2; 
							break; 
					}	
		
				b++; 
				a--; 
			}	
		}
		j++;
		i--; 
		
	}
	return 0; 
}
//Check Diagonally Down and Right for spaces to change:
/**
*@return int 
*@param turn The turn of the current player.
*@param row The row of the cell the player clicked. 
*@param column The column of the cell the player clicked. 
*@param cellSize The size of the cell the player clicked. 
*@param cells The matrix of cells to keep track of where each player has gone. 
*/
int checkDR(int turn, int row, int column, float cellSize, int cells[size][size]){
 
	int i=row; //Row check iteration variable
	int j=column; //Column Check iteration variable; 
	while(cells[i][j]){
		if(i>size-1 || i<0 || j>size-1 || j<0)break; 
	 
		if(cells[i][j] == cells[row][column]){
			int a = row; 
			int b = column; 
			while(b<=j && a<=i){
				if(a>size-1 || a<0 || b>size-1 || b<0)break; 
				
				switch(turn){
						case 1: 	
							drawPiece(1,a, b, cellSize); 
							cells[a][b] = 1; 
							break; 
						case 2: 
							drawPiece(0,a, b, cellSize); 
							cells[a][b] = 2; 
							break; 
					}	
		
				b++; 
				a++; 
			}	
		}
		j++; 	
		i++;
		 
	}
	return 0; 
}
//Check Diagonally Up and Left for spaces to change:
/**
*@return int 
*@param turn The turn of the current player.
*@param row The row of the cell the player clicked. 
*@param column The column of the cell the player clicked. 
*@param cellSize The size of the cell the player clicked. 
*@param cells The matrix of cells to keep track of where each player has gone. 
*/
int checkUL(int turn, int row, int column, float cellSize, int cells[size][size]){
	 
	int i=row; //Row check iteration variable
	int j=column; //Column Check iteration variable; 
	while(cells[i][j]){
		if(i>size-1 || i<0 || j>size-1 || j<0)break; 
		
		
		if(cells[i][j] == cells[row][column]){
			int a = row; 
			int b = column; 
			while(a>=i&&b>=j){
				if(a>size-1 || a<0 || b>size-1 || b<0)break; 
				
				switch(turn){
						case 1: 	
							drawPiece(1,a, b, cellSize); 
							cells[a][b] = 1; 
							break; 
						case 2: 
							drawPiece(0,a, b, cellSize); 
							cells[a][b] = 2; 
							break; 
					}	
				a--; 
				b--; 
			}	
		}
		j--; 
		i--;
	}
	return 0; 
}


//Check Diagonally Down and Left for spaces to change:
/**
*@return int 
*@param turn The turn of the current player.
*@param row The row of the cell the player clicked. 
*@param column The column of the cell the player clicked. 
*@param cellSize The size of the cell the player clicked. 
*@param cells The matrix of cells to keep track of where each player has gone. 
*/
int checkDL(int turn, int row, int column, float cellSize, int cells[size][size]){
	
	int i=row; //Row check iteration variable
	int j=column; //Column Check iteration variable; 
	while(cells[i][j]){
		if(i>size-1 || i<0 || j>size-1 || j<0)break; 
	
		
		if(cells[i][j] == cells[row][column]){
			int a = row; 
			int b = column; 
			while(b>=j&&a<=i){
				if(a>size-1 || a<0 || b>size-1 || b<0)break; 
			
				switch(turn){
						case 1: 	
							drawPiece(1,a, b, cellSize); 
							cells[a][b] = 1; 
							break; 
						case 2: 
							drawPiece(0,a, b, cellSize); 
							cells[a][b] = 2; 
							break; 
					}	
				a++; 
				b--; 
			}	
		}
		j--; 
		i++;
	}

	return 0; 
}



