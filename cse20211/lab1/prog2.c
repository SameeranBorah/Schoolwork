//This program will calculate a score by a football team.  
#include <stdio.h> 

//main method: 
int main(void) { 

	//Declare Variables
	int touchDowns = 0; 
	int extraPoints = 0; 
	int fieldGoals = 0; 
	int safeties = 0; 

	//Prompt user and get input
	printf("Enter the number of touchdowns, extra points, field goals,\n"); 
	printf("and safeties that the team has made, separated by commas.\n"); 
	scanf("%d,%d,%d,%d",&touchDowns, &extraPoints, &fieldGoals, &safeties); 

	//Calculate score
	int score = (touchDowns*6)+(extraPoints)+(fieldGoals*3)+(safeties*2); 
	
	//Output score
	printf("The team has %d points!\n",score); 

	return 0; //End 

}

