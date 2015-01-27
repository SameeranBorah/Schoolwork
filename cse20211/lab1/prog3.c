//This program will tell you the force between two 
//objects a distance r apart with masses m1 and m2. 

#include <stdio.h>
#include <math.h> 

int main(void){
	
	//Declare Variables	
	double G = 6.67E-11; 
	float m1 = 0; 
	float m2 = 0; 
	float r  = 0; 

	//Prompt user and get inputs
	puts("This program will calculate gravitational force."); 
	puts("Enter the mass of the first object (kg)."); 
	scanf("%f",&m1); 
	puts("Enter the mass of the second object (kg)."); 
	scanf("%f",&m2); 
	puts("Enter the distance between the objects (m)."); 
	scanf("%f",&r);  
	
	//Calculate force
	double force = G*m1*m2/(r*r); 
 
	//Make sure the values are correct: 
	if (m1<0||m2<0){
		if(r<=0){
			puts("You cannot have a negative mass and a distance less than or equal to zero."); 
		}	
		else{
			puts("You cannot have a negative mass."); 
		}
	}
	else if (r<=0){
		puts("You cannot have a distance that is less than or equal to zero."); 		
	}
	else {
		printf("The force is %g N.\n",force); 
	}//end
}

