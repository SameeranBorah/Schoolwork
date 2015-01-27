//This will graph the function 1+sin(x^3 - 2x^2 + 6x + 7) from 32.82 to 33.4 in increments of 0.001.

#include <math.h> 
#include <stdio.h> 

int main(void){

	//Declare variables
	double X_MIN = 32.82; 
	double X_MAX = 33.4; 
	double Y_MIN = 2; 
	double Y_MAX = 0; 
	int numPound = 0;
	double value = 0; 
	double i; 

	printf("This will graph 1 + sin(x^3 - 2x^2 + 6x + 7) from 32.82 to 33.40).\n\n");  	
	//Construct the graph
	for(i = X_MIN; i <= X_MAX; i += 0.001) {
		value = 1+ sin(pow(i,3) - 2 * (pow(i,2)) + 6*i + 7);  //Obtain y value
		if(value>Y_MAX){
			Y_MAX = value; 
		}
		if(value<Y_MIN){		//Obtain min/max values
			Y_MIN = value; 
		}
		printf("%10.2f%10.2f ",i,value); //Display the x and y values
		numPound = (int) (value / 0.02);  //Calculate the relative number of pound symbols for the specific y value.
		int n; 
		for (n = 1; n <= numPound; n++){	//Print the pound symbols
			printf("#"); 
		}
		printf("\n"); 
	} 
	//Display the min/max values. 
	printf("\n\nThe max value is %.2f and the min value is %.2f.\n",Y_MAX,Y_MIN);
	 
	


}
