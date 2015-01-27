//John Lake 
//carnival.c
//This program will display a variety of movements from a central point

#include <math.h> 
#include <stdio.h> 
#include "gfx.h" 

//Prototype for drawing the polygon: 
void drawPoly(int sides, int xpos, int ypos, float r);
void drawCircle(int radius,int xCenter,int yCenter); 
void drawMainPistons(float angle,int length, int radius, int xCenter, int yCenter,float angle2,int shiftLength,float spinAngle);
void drawSwingingPistons(int xStart, int yStart,float angle1, float angle,int shiftLength); 
void drawShiftingRods(int xStart, int yStart,float angle1, float angle,int shiftLength,float length);
void drawLeftSpinningRods(int xStart, int yStart,int x2Start, int y2Start, float angle);


int main(void){

	//Set some variables for width, height, and time
	int radius = 100;  //Radius of the circle
	int width = 400; 
	int height = 400;
	int numPistons = 10; 
	int xCenter = 200; 
	int yCenter = 200; 
	int t = 100000; 
	int dt = 1000; 

	  
	//Angle used for determining the location of the first pistons
	float angle = 2*M_PI/numPistons;
	float angleOffset = 0; 

	//Angle used for determining the location of the second pistons
	float angle2 = 2*M_PI*3/4; 
	float angle2Change = 0.1;  
		
	//Angle used to spin around the carts: 
	float spinAngle = 0; 
	
	//First Pistons
	int lineR1 = 50; 
	int lineR1Change = 3; 
	
	//Swinging Rod Length: 
	int swingLength=20; 

	//Shifting Rod Length: 
	int shiftLength = 20; 
	int shiftChange=1; 
	

	//Set the condition for the loop and open the window. 
	int stillGoing = 1; 
	gfx_open(width,height,"Carnival"); 
	
	while(stillGoing){
		gfx_clear();  //Clear the screen
		
		angleOffset+=0.01; 
		
	
		//Increment/Alter values each iteration: 
		lineR1+=lineR1Change; 
		if(lineR1>=80 || lineR1<=10){
			lineR1Change*=-1; 
		}
		
		angle2+=angle2Change; 
		if(angle2>=M_PI*7/4||angle2<=M_PI*5/4){
			angle2Change*=-1;		
		}
		
		spinAngle++; 
		if(spinAngle>=2*M_PI) spinAngle=0; 
		
		shiftLength+=shiftChange; 
		if(shiftLength>=70 || shiftLength<=20){
			shiftChange*=-1; 
		}
		
		int i; 
		for(i=1;i<=numPistons;i++){
			drawMainPistons(i*angle+angleOffset,lineR1,radius, xCenter, yCenter,angle2,shiftLength,spinAngle);
			  
		}
	
		//Draw the circle
		drawCircle(radius,xCenter,yCenter);

		//Sleep for a bit, then post the stuff on the screen
		usleep(t); 
		gfx_flush(); 

		//if the user presses q, exit. 
		if(gfx_event_waiting()){

			char c = gfx_wait();

			switch(c){
				case 'q': 
					stillGoing=0; 
					break; 
			}
		}
	}
	return 0; 
}


void drawSpinningRods(int xStart, int yStart,int x2Start, int y2Start, float angle){
	
	//Spinning Rod Length: 
	int spinLength = 20; 

	gfx_color(255,0,0); 
	//Spinning Rods off of the Right ends:
	int x1 = xStart; 
	int y1 = yStart; 
	int x2 = xStart + spinLength* cos(angle); 
	int y2 = yStart + spinLength*-sin(angle); 
	gfx_line(x1,y1,x2,y2); 
	drawCircle(10,x2,y2); 

	int x3 = x2Start; 
	int y3 = y2Start; 
	int x4 = x2Start + spinLength* cos(angle); 
	int y4 = y2Start + spinLength*-sin(angle); 
	gfx_line(x3,y3,x4,y4); 
	drawCircle(10,x4,y4); 
}
void drawShiftingRods(int xStart, int yStart,float angle1,float angle,int shiftLength,float length){

			gfx_color(0,0,255); 
			//Draw the shifting Rods: 
			float angle2 = atan(shiftLength/2/length); 
			float dirLength = pow(pow((shiftLength/2),2) + pow(length,2),0.5);
			int x1 = xStart + dirLength * cos(angle+angle2);  
			int y1 = yStart + dirLength * -sin(angle+angle2);  
			int x2 = xStart + dirLength * cos(angle-angle2);   
			int y2 = yStart + dirLength * -sin(angle-angle2);    
			gfx_line(x1,y1,x2,y2);  
			drawSpinningRods(x1, y1,x2,y2,angle1);

}
void drawSwingingPistons(int xStart, int yStart,float angle1, float angle,int shiftLength){
		gfx_color(255,0,255); 
		float length = 20; 	
		int x1 = xStart;
		int y1 = yStart; 
		int x2 = length*cos(angle) + x1;  
		int y2 = length*-sin(angle) + y1; 
		gfx_line(x1,y1,x2,y2); 
		drawShiftingRods(x1,y1,angle1,angle,shiftLength,length); 
	
}
void drawMainPistons(float angle,int length, int radius, int xCenter, int yCenter,float angle2,int shiftLength,float spinAngle){
			gfx_color(255,255,0); 
			int x1 = radius* cos(angle)+xCenter; 
			int y1 = radius* -sin(angle)+yCenter;
			int x2= (length+radius)* cos(angle)+xCenter;
			int y2= (length+radius)* -sin(angle)+yCenter;
			gfx_line(x1,y1,x2,y2); 
			drawSwingingPistons(x2,y2,spinAngle,angle2,shiftLength); 
}
void drawCircle(int radius,int xCenter,int yCenter){
	drawPoly(50,xCenter,yCenter,radius); 
}

void drawPoly(int sides, int xpos, int ypos, float r){
	//Initialize variables for function
	float i = 0;
	float angle = (M_PI*2)/sides;
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
