//John Lake 
//numbers.c 
//Displays a window in which the user can place numbers of varying sizes by pressing the number keys

#include "gfx.h" 
#include <stdio.h>
#include <math.h> 


//Function Prototypes: 
void draw_zero(int x, int y, int height); 
void draw_one(int x, int y, int height); 
void draw_two(int x, int y, int height);
void draw_three(int x, int y, int height);
void draw_four(int x, int y, int height);
void draw_five(int x, int y, int height);
void draw_six(int x, int y, int height);
void draw_seven(int x, int y, int height);
void draw_eight(int x, int y, int height);
void draw_nine(int x, int y, int height);


//Main function
int main(void){

	//Initialize the window: 
	gfx_open(400,400,"Numeric Typewriter"); 

	//Necessary variables: 
	int stillGoing = 1; 
	int xPos; 
	int yPos; 
	int size = 100; 


	//Main loop: 
	while(stillGoing){
		//Obtain the key pressed by the user: 
		char c = gfx_wait();

		//Obtain the position of the user's mouse 	
		xPos = gfx_xpos(); 
		yPos = gfx_ypos(); 

		//Perform the appropriate action: 
		switch(c){
			case 'q': 
				stillGoing = 0; 
				break; 
			case '0': 
				draw_zero(xPos,yPos,size); 
				break; 
			case '1':
				draw_one(xPos,yPos,size); 
				break;  
			case '2': 
				draw_two(xPos,yPos,size); 
				break; 
			case '3': 
				draw_three(xPos,yPos,size); 
				break; 
			case '4': 
				draw_four(xPos,yPos,size); 	
				break; 
			case '5': 
				draw_five(xPos,yPos,size); 
				break; 
			case '6': 
				draw_six(xPos,yPos,size); 
				break; 
			case '7': 
				draw_seven(xPos,yPos,size); 
				break; 
			case '8': 
				draw_eight(xPos,yPos,size); 	
				break; 
			case '9': 
				draw_nine(xPos,yPos,size); 
				break; 
			case 'c': 
				gfx_clear(); 	
				break; 
			case '=':
				size*=2; 
				break; 
			case '-':
				size/=2; 
				break; 	
		}
	}	 
	return 0; 
}


//Functions Used: 
void draw_zero(int x, int y, int height){
	int width = height/2; 
	gfx_line(x-(width/2),y-(width),x+(width/2),y-(width)); 	//Top 
	gfx_line(x+(width/2),y+(width),x+(width/2),y-(width)); 	//Right Side
	gfx_line(x-(width/2),y+(width),x-(width/2),y-(width)); 	//Left Side
	gfx_line(x-(width/2),y+(width),x+(width/2),y+(width));  //Bottom
}
void draw_one(int x, int y, int height){
	int width = height/2; 
	gfx_line(x-(width/2),y+(width),x+(width/2),y+(width));  //Bottom
	gfx_line(x,y+(width),x,y-(width)); 			//Middle
	gfx_line(x-(width/2),y-(height/4),x,y-(width)); 	//Flag
}
void draw_two(int x, int y, int height){
	int width = height/2; 
	gfx_line(x-(width/2),y+(width),x+(width/2),y+(width));  //Bottom
	gfx_line(x-(width/2),y+(width),x-(width/2),y); 		//Bottom Left
	gfx_line(x-(width/2),y,x+(width/2),y); 			//Middle Layer
	gfx_line(x+(width/2),y,x+(width/2),y-(width)); 		//Top right
	gfx_line(x-(width/2),y-(width),x+(width/2),y-(width)); 	//Top
}
void draw_three(int x, int y, int height){
	int width = height/2; 
	gfx_line(x+(width/2),y+(width),x+(width/2),y-(width)); 	//Right Side
	gfx_line(x-(width/2),y+(width),x+(width/2),y+(width)); 	//Bottom
	gfx_line(x-(width/2),y,x+(width/2),y); 			//Middle
	gfx_line(x-(width/2),y-(width),x+(width/2),y-(width)); 	//Top
}
void draw_four(int x, int y, int height){
	int width = height/2; 
	gfx_line(x+(width/2),y+(width),x+(width/2),y-(width)); 	//Right Side
	gfx_line(x+(width/2),y,x-(width/2),y); 			//Middle Layer
	gfx_line(x-(width/2),y,x-(width/2),y-(width));		//Top Left
}
void draw_five(int x, int y, int height){
	int width = height/2; 
	gfx_line(x-(width/2),y+(width),x+(width/2),y+(width));  //Bottom
	gfx_line(x+(width/2),y+(width),x+(width/2),y);       	//Bottom right
	gfx_line(x-(width/2),y,x+(width/2),y); 			//Middle Layer
	gfx_line(x-(width/2),y,x-(width/2),y-(width)); 		//Top Left
	gfx_line(x-(width/2),y-(width),x+(width/2),y-(width)); 	//Top
}
void draw_six(int x, int y, int height){
	int width = height/2; 
	gfx_line(x-(width/2),y+(width),x+(width/2),y+(width));  //Bottom
	gfx_line(x+(width/2),y+(width),x+(width/2),y);       	//Bottom right
	gfx_line(x-(width/2),y+(width),x-(width/2),y);    	//Bottom left
	gfx_line(x-(width/2),y,x+(width/2),y); 			//Middle layer
	gfx_line(x-(width/2),y,x-(width/2),y-(width)); 		//Top left
	gfx_line(x-(width/2),y-(width),x+(width/2),y-(width)); 	//Top 
}
void draw_seven(int x, int y, int height){
	int width = height/2; 
	gfx_line(x-(width/2),y-(width),x+(width/2),y-(width)); 	//Top 
	gfx_line(x+(width/2),y+(width),x+(width/2),y);       	//Bottom right
	gfx_line(x+(width/2),y,x+(width/2),y-(width)); 		//Top right
}
void draw_eight(int x, int y, int height){
	int width = height/2; 
	gfx_line(x-(width/2),y-(width),x+(width/2),y-(width)); 	//Top 
	gfx_line(x+(width/2),y+(width),x+(width/2),y-(width)); 	//Right Side
	gfx_line(x-(width/2),y+(width),x-(width/2),y-(width)); 	//Left Side
	gfx_line(x-(width/2),y,x+(width/2),y); 			//Middle layer
	gfx_line(x-(width/2),y+(width),x+(width/2),y+(width));  //Bottom
}
void draw_nine(int x, int y, int height){
	int width = height/2; 
	gfx_line(x-(width/2),y-(width),x+(width/2),y-(width)); 	//Top 
	gfx_line(x+(width/2),y+(width),x+(width/2),y-(width)); 	//Right Side
	gfx_line(x-(width/2),y,x+(width/2),y); 			//Middle layer
	gfx_line(x-(width/2),y,x-(width/2),y-(width)); 		//Top left
}

