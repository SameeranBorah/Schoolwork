//This program will display an integer multiplication table.
#include <stdio.h>


int main(void){

	//Declare variables
	int width = 0; 
	int height = 0;
	unsigned int i = 0; 
	unsigned int j = 0;
	unsigned int mult = 0;

	//Prompt user for width and height
	printf("Multiplication Table:\n\n"); 
	printf("Enter the width of the table.\n"); 
	scanf("%u",&width); 
	printf("Enter the height of the table.\n"); 
	scanf("%u",&height); 

	if (width < 0 || height < 0){
		printf("You cannot have a negative width or height.\n\n"); 
		return 0;    
	}
	//Print the table: 

	printf("Height:%d\n",height); 
	printf("Width:%d\n",width); 

	while(j<=height){  //Outer loop (for height; the table will print line by line.)
		i=0;      					//Every line you need to reset i to 0. 
		while(i<=width){   				//Inner loop (going across the line. 	
			if(j==0){    				//If the height is zero, pring the first line. 
				if (j==0 && i==0){      	//If BOTH are 0, print the *. 
					printf("%4s","*");  	
				}	
				else if(i==width){
					printf("%4u\n",i);   	//If it is the end of the line, move to a new one. 
				}else{
					printf("%4u",i);  	//Print each number. 
				}
			}
			else if (i ==0){    

				printf("%4u",j);  //If it is not the first line, but i==0, print j.  

			}
			else if (i==width){   //if it isn't the first line, and the line is over, make new line. 
				mult = i*j; 
				printf("%4u\n",mult); 
			}
			else{
				mult = i*j;
				printf("%4u",mult);   //Other than the above, print each number. 
			}

			i++; 		
		}			//Increment i and j for each loop. 
		j++;
	}

}//End of main
