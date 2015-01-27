//John Lake 
//carnival.c
//This program will display a variety 

#include <math.h> 
#include <stdio.h> 
#include "gfx.h" 

//Prototypes 
void drawPoly(int sides, int xpos, int ypos);

void drawStar(float sides, float xpos, float ypos);
void drawSpiral(int r,float t,int x, int y);

int main(void){

	
	int width = 400; 
	int height = 400; 
	int xCenter = 200; 
	int yCenter = 200; 
	int angle1 = 0;
	int angle2 = 0;  
	int lineRadius = 30; 
	int lxPos1; 
	int lyPos1;
	int lxPos2; 
	int lyPos2; 
	int lVel = 20; 
	int stillGoing = 1; 
	int sx = rand()%width+1; 
	int sy = rand()%height+1; 
	gfx_open(width,height,"Carnival"); 
	
	float t = 0.1; 
	int starCount = 3; 

	int ball1X = 0; 
	int ball1Y = 200; 
	int ball1VX = 20; 
	int ball1VY = -20; 
	int ball1AY = 10; 

	int ball2X = width; 
	int ball2Y = 300; 
	int ball2VX = -20; 
	int ball2VY = -30; 
	int ball2AY = 10; 

	

		
	

	while(stillGoing){
		gfx_clear(); 
		
		lineRadius+=lVel; 
		if(lineRadius>=380 || lineRadius<= 20){
			lVel*=-1; 
		}

		t+=0.2; 
		if(t>=1)t=0.1; 
		
		ball1X+=ball1VX; 
		ball1Y+=ball1VY; 
		ball1VY +=ball1AY; 

		ball2X+=ball2VX; 
		ball2Y+=ball2VY; 
		ball2VY +=ball2AY;

		if(ball1X>=width) ball1X=0; 
		if(ball1Y>=height){
			ball1Y = height; 
			ball1VY= -50;
		}

		if(ball2X<=0) ball2X=width; 
		if(ball2Y>=height){
			ball2Y = height; 
			ball2VY= -70;
		}

	
		gfx_color(255,0,255); 
		drawPoly(40,ball1X,ball1Y); 
		gfx_color(0,255,0); 
		drawPoly(40,ball2X,ball2Y);
		 
		int r=300; 
		gfx_color(t*200+40,t*200+40,0); 
		drawSpiral(r,t,xCenter,yCenter); 
		
		angle1++; 
		angle2++; 
		if(angle1 >= M_PI*2) angle1 = 0; 
		if(angle2 >= M_PI*2) angle2 = 0;
		lxPos1 = lineRadius * cos(angle1) + xCenter; 
		lyPos1 = lineRadius * -sin(angle1) + yCenter; 
		lxPos2 = lineRadius/5 * cos(angle2) + lxPos1; 
		lyPos2 = lineRadius/5 * -sin(angle2) + lxPos2; 
		
		
		drawStar(starCount,sx,sy); 
		starCount++; 
		if(starCount>=20){
			starCount=3; 
			sx = rand()%width+1; 
			sy = rand()%height+1; 
		}

			 
		gfx_line(xCenter,yCenter,lxPos1,lyPos1); 	
		gfx_line(lxPos1,lyPos1,lxPos2,lyPos2); 	
		
		usleep(100000); 
		gfx_flush(); 

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

void drawSpiral(int r,float t, int x, int y){
	float i; 
	float angle=0; 

	for(i=0;i<=r;i+=t){
		
		angle+=0.1; 
		if(angle>=2*M_PI){
			angle=0; 		
		}
		int x1 = i*cos(angle)+x; 
		int y1 = i*-sin(angle)+y; 
		int x2 = i*cos(angle+0.1)+x; 
		int y2 = i*-sin(angle+0.1)+y; 
		gfx_line(x1,y1,x2,y2); 
	}
}

void drawStar(float sides, float xpos, float ypos){
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
