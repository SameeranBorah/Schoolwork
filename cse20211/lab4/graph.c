//John Lake 
//graph.c 
//Displays the graph of the taylor-series expansion of sin(x) 

#include "gfx.h" 
#include <stdio.h> 
#include <math.h> 

//Prototype Functions
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
void draw_ten(int x, int y, int height,int negative);
void drawAxes(int xCenter, int yCenter, int width, int height); 
void refresh(int width, int height);
void plotFunction(int width, int height,float x,int n); 
int factorial(int n); 


int main(void){
	//Set initial variables
	int width = 1000; 
	int height = 600; 
	int stillGoing = 1; 
	int n = 1; 
	float j=0; 
	
	//Open the window and set the axes
	gfx_open(width,height,"Graph"); 	
	refresh(width,height);
	gfx_color(0,255,0); 

	//Plot the function, starting with n=5
	for(j=-10;j<=10;j+=0.1){
		plotFunction(width,height,j,n); 
	}
	gfx_color(255,255,255); 
	draw_one(300,100,30); 
	//Main loop: 
	while(stillGoing){
		//Refresh the axes:
		refresh(width,height);
		//Obtain user input: 
		char c= gfx_wait(); 	

		//Perform the appropriate task for each key: 
		switch(c){
			case 'q': 
				stillGoing =0; 
				break; 
			case '-': 
				gfx_clear(); 
				n-=2; 
				if(n<=1){
					n=1; 
				} 
				break; 
			case '=':
			case '+': 
				gfx_clear(); 
				n+=2; 
				if(n>21){
					n=21; 
				}
				break; 
			


		}

		//Draw the Number on the screen: 
		switch(n){
			case 1: 
				draw_one(300,100,30); 
				break; 
			case 3: 
				draw_three(300,100,30); 
				break;
			case 5: 
				draw_five(300,100,30);
				break; 
			case 7: 		
				draw_seven(300,100,30); 
				break; 
			case 9:
				draw_nine(300,100,30); 
				break; 
			case 11: 
				draw_one(300,100,30); 
				draw_one(316,100,30); 
				break; 
			case 13: 
				draw_one(300,100,30);
				draw_three(316,100,30);
				break; 
			case 15: 
				draw_one(300,100,30); 
				draw_five(316,100,30);
				break; 
			case 17: 
				draw_one(300,100,30); 
				draw_seven(316,100,30);
				break; 
			case 19:
				draw_one(300,100,30); 
				draw_nine(316,100,30);
				break; 
			case 21: 
				draw_two(300,100,30); 
				draw_one(316,100,30);	
				break; 	

		}
		//Plot the function again: 
		gfx_color(0,255,0); 
		for(j=-10;j<=10;j+=0.1){
			plotFunction(width,height,j,n); 
		}
	}	
}


//Function to draw the axes: 
void drawAxes(int xCenter, int yCenter, int width, int height){
	gfx_line(xCenter-(width/2),yCenter,xCenter+(width/2),yCenter); 		//X-axis 
	gfx_line(xCenter,yCenter-(height/2),xCenter,yCenter+(height/2)); 	//Y-axis 

	int xTicks = width/20;   //Number of x and y tick marks 
	int yTicks = height/20; 
	
	int offset = 5;   //Space above/below axis for tick mark


	int i; 
	for(i=0;i<width;i+=xTicks){
		gfx_line(i,yCenter+offset,i,yCenter-offset); 	//Draw x-ticks
	}
	for(i=0;i<height;i+=yTicks){
		gfx_line(xCenter+offset,i,xCenter-offset,i); 	//Draw y-ticks
	}
	//Send the info to the screen. 
	gfx_flush(); 
}




//Clears the graph and draws the axes 
void refresh(int width,int height){
	gfx_color(255,255,255); 
	drawAxes(width/2,height/2,width,height);
	draw_ten(30,height/2+25,30,1); 
	draw_ten(width-30,height/2+25,30,0); 
	draw_ten(width/2+25,height-30,30,1); 
	draw_ten(width/2+25,30,30,0); 
	gfx_flush(); 
}

//Draws the function value at a point
void plotFunction(int width, int height, float x, int n){
	int xCenter = width/2; 
	int yCenter = height/2; 
	int i; 
	int count = 1; 
	float y=0;

	//Taylor series approximation:
	for(i=1; i<=n;i+=2){
		if(count%2==0){
			y-= pow(x,i)/factorial(i);
		}
		else{
			y+= pow(x,i)/factorial(i);
		}
		count++; 
	 
	}
	x = xCenter + (width/20)*x; 
	y = yCenter - (height/20)*y; 

	//Plots a point at that spot.  The string of points will create the approximation
	gfx_line(x,y,x+1,y); 
	
}
//Returns the factorial of n
int factorial(int n){
	if(n==1 || n==0){
		return 1; 
	}
	else{
		return n* factorial(n-1); 	
	}
}

//Functions for numbers
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

void draw_ten(int x, int y, int height,int negative){
	int width = height/2; 
	gfx_line(x-(width/2),y+(width),x+(width/2),y+(width));  //Bottom
	gfx_line(x,y+(width),x,y-(width)); 			//Middle
	gfx_line(x-(width/2),y-(height/4),x,y-(width)); 	//Flag

	gfx_line(1+width+ x-(width/2),y-(width),1+width+ x+(width/2),y-(width)); 	//Top 
	gfx_line(1+width+ x+(width/2),y+(width),1+width+ x+(width/2),y-(width)); 	//Right Side
	gfx_line(1+width+ x-(width/2),y+(width),1+width+ x-(width/2),y-(width)); 	//Left Side
	gfx_line(1+width+ x-(width/2),y+(width),1+width+ x+(width/2),y+(width));  //Bottom

	if(negative){
		gfx_line(x-width,y,x-(width/2),y); 
	
	}

}
