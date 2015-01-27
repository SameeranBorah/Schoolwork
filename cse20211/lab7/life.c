//John F. Lake, Jr. 
//life.c  
//Conway's Game of Life

#include <stdio.h> 
#define BOARD_SIZE 40


void clearScreen(void);

void removeCell(int cells[BOARD_SIZE][BOARD_SIZE],int i, int j);
void addCell(int cells[BOARD_SIZE][BOARD_SIZE], int i, int j);
void displayCells(int cells[BOARD_SIZE][BOARD_SIZE]);
void updateCells(int cells[BOARD_SIZE][BOARD_SIZE]); 
int getRightBound(int i, int j, int cells[BOARD_SIZE][BOARD_SIZE]);
int getLeftBound(int i, int j,int cells[BOARD_SIZE][BOARD_SIZE]);
int getUpBound(int i, int j,int cells[BOARD_SIZE][BOARD_SIZE]);
int getDownBound(int i, int j,int cells[BOARD_SIZE][BOARD_SIZE]); 
int getNeighbors(int i, int j,  int cells[BOARD_SIZE][BOARD_SIZE]);

int main(void){


	
	int cells[BOARD_SIZE][BOARD_SIZE]; 
	int i,j,stillGoing = 1,checkForInput = 1; 
	
	for(i=0;i<BOARD_SIZE;i++){
		for(j=0;j<BOARD_SIZE;j++){
			cells[i][j] = 0; 
		}
	}
	
	while(stillGoing){
		
		char c; 
		if(checkForInput){
			printf("Enter your input:"); 
			scanf(" %c",&c); 
				switch(c){
					case 'q': 
						stillGoing = 0; 
						break; 
					case 'a':  //Coordinates for adding a cell. 
						printf("Give coordinates (row column) for adding a cell.\n"); 
						scanf("%d %d",&i,&j); 
						addCell(cells,i,j); 
						displayCells(cells); 
						break; 
					case 'r': //Coordinates for removing a cell. 
						printf("Give coordinates (row column) for removing a cell.\n");
						scanf("%d %d",&i,&j); 
						removeCell(cells,i,j);
						displayCells(cells);  
						break; 	
					case 'n': //advance the simulation one tick.
						updateCells(cells);
  
						break; 
					case 'p': 
						checkForInput = 0; 
						break; 


			}	
		}else{
			updateCells(cells); 
			usleep(10000); 
		}
	

		
		

	}

}
void clearScreen(void){
	printf("\033[2J\033[H");
}


void removeCell(int cells[BOARD_SIZE][BOARD_SIZE],int i, int j){
	if(i>= BOARD_SIZE|| j >= BOARD_SIZE || i<0 || j<0 ){
		printf("Those coordinates are outside of the bounds."); 
		return; 
	}
	cells[i][j] = 0; 
}

void addCell(int cells[BOARD_SIZE][BOARD_SIZE], int i, int j){
	if(i>= BOARD_SIZE|| j >= BOARD_SIZE || i<0 || j<0 ){
		printf("Those coordinates are outside of the bounds."); 
		return; 
	}
	cells[i][j] = 1; 
}

void displayCells(int cells[BOARD_SIZE][BOARD_SIZE]){
	clearScreen(); 
	int i,j; //i will be rows, j will be columns. 
	printf("Board:\n"); 
	for(i=0;i<BOARD_SIZE;i++){
		printf("|"); 
		for(j=0;j<BOARD_SIZE;j++){
			if(cells[i][j]==1){
				printf(" X"); 
			}
			else{
				printf("  "); 
			}
		}
		//After every row, go to a new line: 
		printf("|\n"); 
	}
	usleep(3000); 
}


void updateCells(int cells[BOARD_SIZE][BOARD_SIZE]){

	int i,j; //Row,Column	

	
	int temp[BOARD_SIZE][BOARD_SIZE]; 
	for(i=0;i<BOARD_SIZE;i++){
		for(j=0;j<BOARD_SIZE;j++){
			temp[i][j] = cells[i][j]; 
		}
	}

	
	for(i=0;i<BOARD_SIZE;i++){
		for(j=0;j<BOARD_SIZE;j++){
		
			int neighbors = getNeighbors(i,j,cells);


			if(cells[i][j]==1){   //Cell is alive: 
				neighbors--; //Don't count the cell itself as a neighbor. 
				if(neighbors<2 || neighbors>3) temp[i][j]=0; 	
			}
			else{  //Cell is dead: 
				if(neighbors == 3){
					 temp[i][j]=1; 
				}
			}
		}
	}
	for(i=0;i<BOARD_SIZE;i++){
		for(j=0;j<BOARD_SIZE;j++){
			cells[i][j] = temp[i][j]; 
		}
	}
	usleep(2000); 
	displayCells(cells); 	
}



//These 4 functions check to see if a cell is at a corner or the edge of the board. 
int getRightBound(int i, int j, int cells[BOARD_SIZE][BOARD_SIZE]){
	if(i == BOARD_SIZE-1) return BOARD_SIZE-1; 
	return i+1; 
}
int getLeftBound(int i, int j,int  cells[BOARD_SIZE][BOARD_SIZE]){
	if(i == 0) return 0; 
	return i-1; 

}
int getUpBound(int i, int j, int cells[BOARD_SIZE][BOARD_SIZE]){
	if(j == 0) return 0; 
	return j-1; 

}
int getDownBound(int i, int j,int  cells[BOARD_SIZE][BOARD_SIZE]){
	if(j == BOARD_SIZE-1) return BOARD_SIZE-1; 
	return j+1; 

}


//Get the surrounding 
int getNeighbors(int i, int j,  int cells[BOARD_SIZE][BOARD_SIZE]){
	int neighbors = 0; 
	int left,right,up,down; //Bounds
	left = getLeftBound(i,j,cells); 
	right = getRightBound(i,j,cells);
	up = getUpBound(i,j,cells); 
	down = getDownBound(i,j,cells); 
			
			
	int x,y; 
	for(x = left;x<=right;x++){
		for(y=up;y<=down;y++){
			if(cells[x][y]==1) neighbors++; 
		}
	}
	return neighbors; 
}
