//This program will display different symbols based on input from the user.

#include <stdio.h> 
#include "gfx.h" 
#include <math.h> 


void drawPoly(int sides,int xpos, int ypos); //Prototype function

//Main method
int main(void){
	
	//Declare variables
	char c; 
	int stillGoing = 1; 
	int x; 
	int y; 

	//Initialize window
	gfx_open(300,300,"Symbols"); 
	

	//While loop for the program; ends when Q or q is pressed
	while(stillGoing){ 
		
		//Get user input for the mouse location
		c = gfx_wait(); 
		x = gfx_xpos(); 
	        y = gfx_ypos(); 
		
		//Determine which key was pressed
		switch(c){

			//If the mouse was clicked, draw a 20x20 square
			case 1:
				gfx_color(0,0,255); 
			 	gfx_line(x-20,y-20,x+20,y-20); 
			 	gfx_line(x-20,y-20,x-20,y+20); 
			 	gfx_line(x+20,y+20,x+20,y-20); 
			 	gfx_line(x+20,y+20,x-20,y+20); 
			break; 

			//If T or t is pressed, draw a triangle
			case 't':
			case 'T': 
				gfx_color(0,255,0); 
				gfx_line(x-10,y-10,x,y+10); 
				gfx_line(x-10,y-10,x+10,y-10);
				gfx_line(x,y+10,x+10,y-10);  
			break; 
		
			//If C is pressed, draw a circle
			case 'c':
			case 'C':

				gfx_color(255,255,255); 
				float dt = 0.05; 
				float r = 10; 
				float t = 0;
				float x1; 
				float x2; 
				float y1; 
				float y2; 
 
				for(t = 0 ; t < 2*M_PI ; t += dt){
					x1 = r * cos(t) + x; 
					y1 = r * -sin(t) + y; 
					x2 = r * cos(t+dt) + x; 
					y2 = r * -sin(t) + y; 
					gfx_line(x1,y1,x2,y2); 
				} 
			break; 


			//If 3-9 is pressed, draw a polygon with that many sides. 
			case '3':
			case '4': 
			case '5': 
			case '6': 
			case '7': 
			case '8': 
			case '9': 
				c = c-'0'; 
				gfx_color(255,0,255); //Set color to purple.
				drawPoly((int) c,x,y);

			break; 
			
			//If f or F is pressed, clear the window. 
			case 'f': 
			case 'F': 
				gfx_clear(); 
			break;

			//If q or Q is pressed, end the program
			case 'q': 
			case 'Q':
				stillGoing =0; 
			break; 

		}
					
	}

	return 0; 
}	


//Function used to draw the polygons

void drawPoly(int sides, int xpos, int ypos){

	//Initialize variables for function
	float i = 0;
	float angle = (M_PI*2)/sides;
	float r = 20; 
	float x1; 
	float x2; 
	float y1; 
	float y2; 
	
	for(i=0;i<2*M_PI;i+=angle){
		x1 = r * cos(i) + xpos; 
		y1 = r * -sin(i) + ypos;
		x2 = r * cos(i+angle) + xpos; 
		y2 = r * -sin(i+angle) + ypos; 	
		gfx_line(x1,y1,x2,y2); 
	
	}

}
