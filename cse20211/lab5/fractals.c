#include <stdio.h> 
#include "gfx.h" 
#include <math.h> 


//Function Prototypes 
void draw_triangle(float xStart, float yStart, float width,float height); 
void draw_square(float xStart, float yStart, float width);
void fractal_squares(float xStart, float yStart, float width); 
void fractal_spiral_squares(float xStart, float yStart,float angle, float radius, float width);
void draw_circle(float x, float y, float radius);
void fractal_circular_lace(float x, float y, float radius);
void draw_snowflake(float x, float y, float length);
void draw_tree(float x, float y, float length,float angle); 
void draw_fern(float x, float y, float length, float angle); 
void draw_spiral(float radius, float x, float y);
void fractal_spirals(float radius, float x, float y); 




int main(void){
	//Open the graphics window
	gfx_open(500,500,"Fractals");

	//Used to keep the loop going:  
	int stillGoing = 1; 
	while(stillGoing){
		//Get user input for each shape, and draw them accordingly:
		char c = gfx_wait(); 
		
		switch(c){
			case '1': 
				draw_triangle(20,20,460,460); 
				break; 
			case '2': 
				fractal_squares(110,110,270); 
				break; 
			case '3': 
				fractal_spiral_squares(210,200,6,250,30);
				break; 
			case '4': 
				fractal_circular_lace(250,250,150); 
				break; 
			case '5': 
				draw_snowflake(250,250,150); 
				break; 
			case '6': 
				draw_tree(250,500,150,M_PI/2); 
				break; 
			case '7': 
				draw_fern(250,450,300,M_PI/2); 
				break; 
			case '8': 
				fractal_spirals(400,250,250); 
				break; 
			case 'q': 
				stillGoing = 0; 
				break; 
			case 'c': 
				gfx_clear(); 
				break; 

		}

	}
}



//Functions used: 
void draw_triangle(float xStart, float yStart, float width,float height){
	if(width<1) return;  //Base case

	//Draw a triangle
	gfx_line(xStart,yStart, xStart+width,yStart); 
	gfx_line(xStart,yStart,xStart+(width/2.0),yStart+height); 
	gfx_line(xStart+(width/2.0),yStart+height,xStart+width,yStart);
	
	//Recursively perform the function inside the triangle 3 times
	draw_triangle(xStart,yStart,width/2.0,height/2.0); 
	draw_triangle(xStart+(width/2.0),yStart,width/2.0,height/2.0); 
	draw_triangle(xStart+(width/4.0),yStart+(height/2.0),width/2.0,height/2.0); 
}	
//Function to draw a square
void draw_square(float xStart, float yStart, float width){
	gfx_line(xStart,yStart,xStart+width,yStart); 
	gfx_line(xStart,yStart,xStart,yStart+width); 
	gfx_line(xStart,yStart+width,xStart+width,yStart+width); 
	gfx_line(xStart+width,yStart,xStart+width,yStart+width); 
}


void fractal_squares(float xStart, float yStart, float width){
	if(width<1) return;  //Base case
	//Draw a square at the specified point
	draw_square(xStart,yStart,width); 
	//Reduce the width, and recursively draw the squares at each corner: 
	width/=5.0; 
	fractal_squares(xStart-(width),yStart-(width),2*width); 
	fractal_squares(xStart-(width),yStart+(width*4),2*width); 
	fractal_squares(xStart+(width*4),yStart-(width),2*width); 
	fractal_squares(xStart+(width*4),yStart+(width*4),2*width); 
}

void fractal_spiral_squares(float xStart, float yStart, float angle, float radius, float width){	
		if(width<1) return;  //Base case

		if(angle<=0) angle = 2*M_PI;  //If the angle hits zero, reset to 2pi. 
		if(radius<=0) radius = 0;  //Prevent the radius from becoming negative
		
		float x = radius*cos(angle)+xStart;   //Obtain the location of where to draw the square
		float y = -radius*sin(angle)+yStart; 
		draw_square(x,y,width); //Draw it
	
		fractal_spiral_squares(xStart,yStart,angle-0.5,radius-8,width-1); //Perform the function recursively, making it spiral. 
		
}
//Function used to draw circles:
void draw_circle(float x, float y, float radius){
	float i; 
	for(i=0;i<2*M_PI;i+=0.01){
		float x1 = x+radius*cos(i); 
		float y1 = y-radius*sin(i); 
		float x2 = x+radius*cos(i+0.01); 	
		float y2 = y-radius*sin(i+0.01); 
		gfx_line(x1,y1,x2,y2); 
	}


}

void fractal_circular_lace(float x, float y, float radius){
	if(radius<=4) return;  //Base case
		
	draw_circle(x,y,radius); //Draw a circle at the center
	float i; 
	//Draw 5 circles around it, and perform the function recursively on those circles
	for(i = 0;i<M_PI*2;i+=M_PI/3){ 		
		fractal_circular_lace(x+radius*cos(i),y-radius*sin(i),radius/3); 
	}

}

void draw_snowflake(float x, float y, float length){
	if(length<=1) return;  //Base case
	float i; 
	//Draw branches from the center, and perform the function recursively at the endpoint of each branch: 
	for(i=2*M_PI/5;i<=2*M_PI+2*M_PI/5;i+=2*M_PI/5){
		float x2 = x+length*cos(i); 
		float y2 = y-length*sin(i); 
		gfx_line(x,y,x2,y2); 
		draw_snowflake(x2,y2,length/3); 
	}
}

void draw_tree(float x, float y, float length,float angle){
	if(length<=0.5) return;  //Base case
	//Draw a branch
	float x2 = x + length*cos(angle); 
	float y2 = y - length*sin(angle); 
	gfx_line(x,y,x2,y2); 
	//Recursively draw two branches off of the first one
	draw_tree(x2,y2,length/1.5,angle+M_PI/5); 
	draw_tree(x2,y2,length/1.5,angle-M_PI/5); 
}

void draw_fern(float x, float y, float length, float angle){
	if(length<=3) return;  //Base case
		
	//Draw the first branch: 
	float x2 = x + length*cos(angle); 
	float y2 = y - length*sin(angle); 
	gfx_line(x,y,x2,y2); 

	float i; 	
	//Recursively draw 8 branches off of the first one: 
	for(i =length/4;i<=length;i+=length/4){
		float x2 = x + i*cos(angle); 
		float y2 = y - i*sin(angle); 
		draw_fern(x2,y2,length/3,angle+M_PI/5); 
		draw_fern(x2,y2,length/3,angle-M_PI/5); 
	}
}
//Function used to draw a spiral of points: 
void draw_spiral(float radius,float x, float y){
	float i=0;  //i is the angle
	float j=1;  //j is the distance from the central point
	
	while(j<radius){
		i+=M_PI/5; //each point is pi/5 rads apart
		float x1 = x+j*cos(i); 
		float y1 = y-j*sin(i); 
		
		gfx_point(x1,y1); //Plot the point
		 
		j*=1.1; 	//Increase the distance
	}	
}
void fractal_spirals(float radius, float x, float y){
		if(radius<=1) return;  //Base case
		float i = 0;  //i is the angle
		float j = 1;  //j is the distance from the center
		
		//Recursively draw spirals at each point of the large spiral: 
		while(j<radius){
			i+=M_PI/5;  
			float x1 = x+j*cos(i); 
			float y1 = y-j*sin(i); 
			
			draw_spiral(j/3,x1,y1); 
			fractal_spirals(j/3,x1,y1); 
			j*=1.1; 
		}	

}


