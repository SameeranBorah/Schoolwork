//This program will display a rotating object that is controlled by the user. 
//John Lake

#include "gfx.h" 
#include <stdio.h> 
#include <math.h> 


//Initialize prototype function
void drawPoly(float sides, float xpos, float ypos); 

//Main function
int main(void){

	//Initialize the graphics window
	gfx_open(400,400,"Spinning Wand"); 


	int sleepTime = 5000; 
	int stillGoing = 1; 
	int sides = 3; 
	int bulletShot=0; 

	float angle = 0;
	float r = 50; 
	float xCenter = 200; 
	float yCenter = 200; 
	float xPos = r * cos(angle) + xCenter; 
	float yPos = r * -sin(angle) + yCenter; 
	float bulletXPos=-50; 
	float bulletYPos=-50; 
	float bulletXVel=0; 
	float bulletYVel=0; 
 

	//Program loop
	while(stillGoing){ 

		//Clear the screen for the next animation iteration
		gfx_clear(); 

		//Change the color 
		gfx_color(255/angle,(int)(5000*angle)%255,255/angle); 
		//Increment the angle; reset to zero if over 2pi
		angle+=0.01; 
		if(angle>=M_PI*2){
			angle = 0; 		
		}
	
		//Obtain the position of the object
		xPos = r * cos(angle) + xCenter; 
		yPos = r * -sin(angle) + yCenter; 

		bulletXPos += bulletXVel; 	
		bulletYPos += bulletYVel;  //Update Position of Bullet


	

		//Draw the image and flush the screen. 
		drawPoly(sides,xPos,yPos);
		gfx_line(xCenter,yCenter,xPos,yPos); 
		drawPoly((int) angle + 3, bulletXPos,bulletYPos);  
		usleep(sleepTime); 
		gfx_flush(); 



		//If user presses a button, execute the action.
		if(gfx_event_waiting()){
			char c = gfx_wait();
			switch(c){
				//If the user presses 'q', quit
				case 'q':
					stillGoing = 0; 
					break; 

				//If the user presses 3-9, switch the form of the object
				case '3':
				case '4': 
				case '5': 
				case '6': 
				case '7': 
				case '8': 
				case '9': 
					c = c-'0'; 
					sides = c; 
					break; 	

				//If the user presses 's', shoot out a star shape	
				case 's': 	
					if(bulletShot==0){
						bulletXVel = 3*cos(angle); 
						bulletYVel = 3*-sin(angle);			
						bulletYPos = yPos;  
						bulletXPos = xPos;
					}
					else{
						bulletShot = 0; 
					}
					break; 

				//If the user presses 't' or 'g', increase or decrease the radius, respectively. 
				case 't': 
					r+=2;
					if(r>=300) r=300;  
					break; 		
				case 'g': 
					r-=2; 
					if(r<=0){
						r=0; //Can't have a negative radius. 
					}
					break; 	

				//If the user presses 'y' or 'h', slow down or speed up the animation, respectively.  
				case 'y': 
					sleepTime+=100;
					if(sleepTime>=12000) sleepTime = 12000;  
					break; 
				case 'h': 
					sleepTime-=100; 
					if(sleepTime<=100) sleepTime = 100; 
					break; 		


			}


	 		
		}		


	}


}



void drawPoly(float sides, float xpos, float ypos){

	//Initialize variables for function
	float i = 0;
	float angle = (M_PI*2)/sides;
	float r = 20; 
	float x1; 
	float x2; 
	float y1; 
	float y2; 
	

	//Draw a star
	for(i=0;i<2*M_PI;i+=angle){
		x1 = r * cos(i) + xpos; 
		y1 = r * -sin(i) + ypos;
		x2 = r * cos(i+angle) + xpos; 
		y2 = r * -sin(i+angle) + ypos; 	
		gfx_line(xpos,ypos,x2,y2); 
	
	}

}
