#include "gfx.h" 
#include <math.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h> 


void drawPoly(int sides, int xpos, int ypos); 


int main(void) {
	

	gfx_open(400,400,"Bounce"); 
	int stillGoing = 1; 
	float dt = 0.01;
	float xpos =rand() %400+1;  
	float ypos =rand() %400+1; 
        float xvel =(double)rand()/RAND_MAX * 10.0 - 5.0; 
	float yvel =(double)rand()/RAND_MAX * 10.0 - 5.0; 
	float RIGHT_EDGE = 400; 
	float LEFT_EDGE = 0; 
	float TOP = 0; 
	float BOTTOM = 400; 

	
	
	while(stillGoing){
		xpos += xvel; 
		ypos += yvel; 
			
		if(xpos <= LEFT_EDGE || xpos >= RIGHT_EDGE) xvel *=-1; 
		if(ypos <= TOP || ypos >= BOTTOM) yvel *= -1; 
		gfx_clear(); 
		drawPoly(30,xpos,ypos); 
		gfx_flush(); 
		usleep(10000); 

		
		if(gfx_event_waiting()){
			char c = gfx_wait(); 
			if(c==1){
				xpos = gfx_xpos(); 		
				ypos = gfx_ypos(); 
			        xvel =(double)rand()/RAND_MAX * 10.0 - 5.0; 
				yvel =(double)rand()/RAND_MAX * 10.0 - 5.0;
			}
			else if (c=='q' || c=='Q'){
				break; 
			}

		}

	}	


	return 0; 

}

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
