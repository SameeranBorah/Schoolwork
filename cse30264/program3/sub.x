/*
	John Lake RPC sub.x file
	Functions used in submarine.c: 
*/


struct inputs{
	int turn; 
	int x1; 
	int y1;
	int x0; 
	int y0; 
	int returnVal;
};
typedef struct inputs inputs;

struct outputs{
	int x0; 
	int y0; 
	int returnVal; 
};
typedef struct outputs outputs; 

     program SUBPROG {
               version SUBVERS {
                    outputs SERVER_MOVE(inputs) = 1;
               } = 1;
          } = 0x31728436;













