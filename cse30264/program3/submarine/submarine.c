/*
	John F. Lake, Jr. 
	submarine.c
	My implementation of the client side of the submarine game   
	The server controls the sub, while the client controls the destroyer.


 */



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sub.h"

#define MAX_GRID 8
#define DURATION 4

//This function will be edited and moved to the server because it deals with how the submarine moves
//int movenpick(int turn, int x1, int y1);


//Client side function

struct depthCharge{
	int x; 
	int y;
	int used; 
}; typedef struct depthCharge dCharge;



void print_map(int x, int y,dCharge d1, dCharge d2, dCharge d3);

//Keep this here; it doesn't need to be done on the server. 
void print_map(int x, int y, dCharge d1, dCharge d2, dCharge d3)
{
 int i, j;
 printf("\nFind the Hidden Submarine: Written by Prof. Joseph Ng\n");
 printf("Ocean Map:\n ");
 for (i = 0; i < MAX_GRID; i++) printf(" %d", i); printf("\n");
 for (i = 0; i < MAX_GRID; i++){
     printf("%d", i);
     for (j = 0; j < MAX_GRID; j++){
         if ((i == y) && (j == x)){
         	 printf(" D"); 
         }else if (d1.used && i == d1.y && j==d1.x){
         	printf(" X"); 
         }else if (d2.used && i == d2.y && j==d2.x){
         	printf(" X"); 
         }else if (d3.used && i == d3.y && j==d3.x){
         	printf(" X"); 
         }else printf(" .");
     }
     printf("\n");
 }
 printf("\n\n\nMessage:\n");
}




int main(int argc, char* argv[])
{	



	if(argc != 2){
		printf("Usage: ./submarine HOSTNAME\n"); 
		exit(0); 
	}
	inputs in; 
	outputs *out;  
	
 
	int done = 0;
	int chargesUsed =0; 
 	in.turn =-1; 
 	int c, dummy, alert;
 	CLIENT *clnt; 
 	
 	//Depth charge variables: 
 	dCharge charge1; charge1.used =0; 
 	dCharge charge2; charge2.used =0; 
 	dCharge charge3; charge3.used =0;

 	
 	
 	
 
 
	//Seed the random # generator and establish starting positions for the destroyer: 
 	srand(37);
 	in.x1 = rand()%MAX_GRID;
 	in.y1 = rand()%MAX_GRID;
 	in.x0 = -1; 
 	in.y0 = -1; 

	//Display the map and show where the distroyer is at: 
 	
 	print_map(in.x1, in.y1,charge1,charge2,charge3);
 	printf("Destroyer Start Position: X = %d   Y = %d\n", in.x1, in.y1);
 	printf("\n\n\n\n\n\n\n");
	clnt = clnt_create(argv[1],SUBPROG,SUBVERS,"tcp"); 

	//Game Loop: 
 	while (!done){
       		printf("Enter Command> ");
       		c = getchar(); dummy = getchar();
       		switch (c){
         		case 'x': printf("Exit on command. Bye!\n"); exit(0);
         		case 'd': //Drop a depth charge for the submarine to hit.  
         			if(chargesUsed < 3){
         				printf("Dropping depth charge...\n"); 
         				switch(chargesUsed){
         					case 0: 
         						//Use first charge: 
         						charge1.x = in.x1; 
         						charge1.y = in.y1; 
         						charge1.used =1; 
         						break; 	
         					case 1: 
         						//Use second charge: 
         						charge2.x = in.x1; 
         						charge2.y = in.y1; 
         						charge2.used =1;
         						break; 
         						
         					case 2: 
         						//Use third charge: 
         						charge3.x = in.x1; 
         						charge3.y = in.y1;
         						charge3.used =1;  
         						break; 
         				
         				}
         				chargesUsed++; 
         			} else printf("NO CHARGES LEFT! YOU WASTED A TURN!!!\n");
         			in.turn++; 
         			break; 
	 		case '7': in.x1 = (in.x1 + MAX_GRID - 1) % MAX_GRID;
	 		case '8': in.y1 = (in.y1 + MAX_GRID - 1) % MAX_GRID; in.turn++; break;
	 		case '9': in.y1 = (in.y1 + MAX_GRID - 1) % MAX_GRID;
	 		case '6': in.x1 = (in.x1 + MAX_GRID + 1) % MAX_GRID; in.turn++; break;
	 		case '3': in.x1 = (in.x1 + MAX_GRID + 1) % MAX_GRID;
	 		case '2': in.y1 = (in.y1 + MAX_GRID + 1) % MAX_GRID; in.turn++; break;
	 		case '1': in.y1 = (in.y1 + MAX_GRID + 1) % MAX_GRID;
	 		case '4': in.x1 = (in.x1 + MAX_GRID - 1) % MAX_GRID; in.turn++; break;
	 		case '5': in.turn++; break;
	 		default : 
	 			printf("Illegal movement: %c\n", c); 
	 			break;
       		}
 		printf("Destroyer Position: X = %d   Y = %d\n", in.x1, in.y1);

       		print_map(in.x1, in.y1,charge1,charge2,charge3);
       		printf("Turn:%3d Dir:%c X = %d   Y = %d\n", in.turn, c, in.x1, in.y1);

       		out = server_move_1(&in,clnt);
       		in.x0 = out->x0; 
       		in.y0 = out->y0; 
       		
       		//check if a depth charge has hit the sub: 
       		if(chargesUsed>=1 && charge1.x == in.x0 && charge1.y == in.y0){
       			printf("A Depth Charge Hit! Congratulation! End game.\n");
       			clnt_destroy(clnt); 
       			return 0; 
       		} else if (chargesUsed >=2 && charge2.x == in.x0 && charge2.y == in.y0){
       			printf("A Depth Charge Hit! Congratulation! End game.\n");
       			clnt_destroy(clnt); 
       			return 0; 
       		} else if (chargesUsed == 3 && charge3.x == in.x0 && charge3.y == in.y0){
       			printf("A Depth Charge Hit! Congratulation! End game.\n");
       			clnt_destroy(clnt); 
       			return 0;  
       		}
       	 
       		switch(out->returnVal){
         		case 0: printf("Hit! Congratulation! End game.\n"); done = 1; break;
         		case 1: printf("Red Alert!!!\n"); break;
         		case 2: printf("Yellow Alert!!\n"); break;
         		case 3: printf("Green Alert!\n"); break;
        		default: break;
       		}
       		printf("\n\n\n");
 	}
 	
	clnt_destroy(clnt); 
 	return 0;
}
