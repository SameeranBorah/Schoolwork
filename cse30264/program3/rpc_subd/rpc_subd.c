/*
	John F. Lake, Jr. 
	rpc_subd.c
	This is the server side of the RPC program, with the implementation of the function.  
*/
#include "sub.h"
#define MAX_GRID 8
#define DURATION 4

outputs * server_move_1_svc(inputs * in, struct svc_req * rqstp){


	static struct outputs out; 
	
	
	//printf("Destroyer at: %d\t%d\n",in->x1,in->y1); 
	
	
	//Initial variables set up: 
 	int deltax1, deltax2, deltay1, deltay2;
 	int sqdistance, deltaxsq, deltaysq;
	int move_dir;

	if (in->turn == 0){ /* generate a submarine on the 8X8 Grid */
    		do{
    			//printf("DEBUG> Making a new submarine!!!!!!\n"); 
       			out.x0 = rand()%MAX_GRID;
       			out.y0 = rand()%MAX_GRID;	
			//printf("DEBUG> Submarine at x=%d Y=%d\n", out.x0, out.y0); 
    		}while ((in->x1 == out.x0) && (in->x1 == out.y0));
 	}

 	//printf("DEBUG>Submarine at X = %d   Y = %d\n", out.x0, out.y0); 

 	if ((out.x0 == in->x1) && (out.y0 == in->x1)) {out.returnVal=0; return (&out);}  /* hit */

 	if (in->turn % DURATION == 0){ /* submarine move */
    		move_dir = rand()%9+1;
 		   //printf("DEBUG>Submarine move at direction %d\n", move_dir); 
    		switch (move_dir){
      			case 7: out.x0 = (in->x0 + MAX_GRID - 1) % MAX_GRID;
      			case 8: out.y0 = (in->y0 + MAX_GRID - 1) % MAX_GRID; break;
     			case 9: out.y0 = (in->y0 + MAX_GRID - 1) % MAX_GRID;
    			case 6: out.x0 = (in->x0 + MAX_GRID + 1) % MAX_GRID; break;
    			case 3: out.x0 = (in->x0 + MAX_GRID + 1) % MAX_GRID;
   			case 2: out.y0 = (in->y0 + MAX_GRID + 1) % MAX_GRID; break;
      			case 1: out.y0 = (in->y0 + MAX_GRID + 1) % MAX_GRID;
      			case 4: out.x0 = (in->x0 + MAX_GRID - 1) % MAX_GRID; break;
      			case 5: break;
     			default: printf("Illegal movement: %d\n", move_dir); break;
    		}
    		//printf("DEBUG>Submarine now at X = %d   Y = %d\n", out.x0, out.y0); 
 	}else printf("\n\n");

 	if (out.x0 > in->x1){ deltax1 = out.x0 - in->x1; deltax2 = in->x1 + MAX_GRID - out.x0; }
    		else{ deltax1 = in->x1 - in->x0; deltax2 = out.x0 + MAX_GRID - in->x1; }
 	if (deltax1 > deltax2) deltaxsq = deltax2 * deltax2;
    		else deltaxsq = deltax1 * deltax1;

 	if (out.y0 > in->x1){ deltay1 = out.y0 - in->x1; deltay2 = in->x1 + MAX_GRID - out.y0; }
    		else{ deltay1 = in->x1 - out.y0; deltay2 = out.y0 + MAX_GRID - in->x1; }
 	if (deltay1 > deltay2) deltaysq = deltay2 * deltay2;
    		else deltaysq = deltay1 * deltay1;

 	sqdistance = deltaxsq + deltaysq;
 	if (sqdistance <= 2) {out.returnVal=1; return (&out);}  /* red alert */
 	if (sqdistance <= 8) {out.returnVal=2; return (&out);} /* yellow alert */
    	else out.returnVal=3; /* green alert */
    	
    	return (&out); 
    	
}
