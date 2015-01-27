#include <stdio.h> 
#include "gfx.h" 
#include <math.h> 


//Recursive function used: 
void draw_snowflake(float x, float y, float length,float density,float angle); 

//Initialize the global variables for widthand height: 
float width = 1200; 
float height = 500; 


int main(void){

	//Open the graphics window: 
	gfx_open(width,height,"Gallery of Fractals"); 

	//Loop for the program: 
	int stillGoing = 1; 
	while(stillGoing){
		  

		//Draw 16 snowflakes of arbitrary values: 
		draw_snowflake(75,150,40,3,1); 
		draw_snowflake(225,150,50,4,.5); 
		draw_snowflake(375,150,30,0.2,1); 
		draw_snowflake(525,150,55,1,2); 
		draw_snowflake(675,150,26,1.3,1.6); 
		draw_snowflake(825,150,65,1.6,M_PI/3); 
		draw_snowflake(975,150,45,1.7,1.2); 
		draw_snowflake(1125,150,35,2.3,2.4); 
		draw_snowflake(75,350,31,2,2.4); 
		draw_snowflake(225,350,75,0.3,2.3); 
		draw_snowflake(375,350,33,2,.56); 
		draw_snowflake(525,350,34,3.1,1.5); 
		draw_snowflake(675,350,53,4.2,.78); 
		draw_snowflake(825,350,56,3.6,1.4); 
		draw_snowflake(975,350,71,3,.4); 
		draw_snowflake(1125,350,42,5.8,1); 
		
		//If the user hits 'q', end the program: 
		char c = gfx_wait(); 
		if(c=='q') stillGoing = 0; 
	}

}
/**
*@returns void
*@param x X Location of Snowflake
*@param y Y Location of Snowflake
*@param length Length of the snowflake branches
*@param density Thickness of the snowflake
*@param angle The angle between successive branches on the snowflake
*/
void draw_snowflake(float x, float y, float length, float density,float angle){
	if(length<=density) return; //Base case
		
	float i; //i is the angle for the current branch drawn: 
	for(i=angle;i<=2*M_PI+angle;i+=angle){
		float x2 = x+length*cos(i); //Obtain the endpoint location for the branch
		float y2 = y-length*sin(i); 
		gfx_line(x,y,x2,y2); //Draw the branch
		draw_snowflake(x2,y2,length/3,density,angle);//Recursively perform the function again for each endpoint 
	}
}

