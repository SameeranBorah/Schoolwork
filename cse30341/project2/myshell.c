/*
 * John F. Lake, Jr. 
 * CSE30341, Project 2
 * Myshell
 *
 */
//Debugging: 
#define DEBUG 1


//Includes: 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

//Defines: 
#define BUF_LEN 4096
#define MAX_ARGS 100
#define EXIT 1
#define START 2
#define WAIT 3
#define RUN 4
#define KILL 5
#define STOP 6
#define CONT 7



/*
 * interpretCommand() determines if a command exists, and returns an integer corresponding with that action
 * @param command The command the user has entered (args[0]).
 * @return int
 */
int interpretCommand(char * command){
	if(strcmp(command,"quit") == 0 || strcmp(command,"Quit") == 0 || strcmp(command,"exit") == 0 || strcmp(command,"Exit") == 0)
		return EXIT;
	else if(strcmp(command,"start")==0) 
		return START;
	else if(strcmp(command,"wait")==0) 
		return WAIT;
	else if(strcmp(command,"run")==0) 
		return RUN;
	else if(strcmp(command,"kill")==0) 
		return KILL;
	else if(strcmp(command,"stop")==0) 
		return STOP;
	else if(strcmp(command,"continue")==0) 
		return CONT;
	else
		printf("myshell: ERROR, Unknown command %s\n",command);
		return -1;
}

/*
 * getInput() returns the number of arguments read
 * @param input The input string from the user.
 * @param args The array of arguments from the user.
 * @param return int
 */
int getInput(char *input, char ** args){
	//Get user input: 
	if(fgets(input,BUF_LEN,stdin)!=NULL){

		//Testing user input: 
		#ifdef DEBUG
			printf("You entered: %s\n",input);
		#endif

		//Interpret the input: 
		//user strtok to separate the input: 
		int argsNo=0;
		while(argsNo<MAX_ARGS){
			//Strtok needs input of NULL after first line, so you need to process the first line differently: 
			if(argsNo==0){
				if((args[argsNo] = strtok(input,"	 \n"))==NULL){
					return -1;
				}else{	
					#ifdef DEBUG
						printf("Command: %s\n",args[argsNo]);
					#endif
					//Increment the number of arguments read: 
					argsNo++;
				}
			}else{
				if((args[argsNo] = strtok(NULL,"	 \n"))==NULL){
					break;
				}else{
					#ifdef DEBUG
						printf("Argument %d: %s\n",argsNo,args[argsNo]);
					#endif
					argsNo++;
				}
			}
		}
		//Return the number of arguments run: 
		return argsNo;
	}else{
		return -1;
	}
}




int main(){

	//args will hold any command line arguments
	char * args[MAX_ARGS];
	char input[BUF_LEN];
	int shellRunning = 1;


	while(shellRunning){

		printf("myshell>");
		int numArgs;
		if((numArgs = getInput(input,args))==-1){
			//Print error message
		}else{
			//Interpret/use the input: 
			switch(interpretCommand(args[0])){
				case EXIT:
					shellRunning =0;
					break;
				case START:;
					//Here, we will fork and call the execvp() function: 
					//TODO: Need to make sure that you check for correct number of args
					pid_t pid = fork();
					//If this is a child process, run: 
					if(pid<0){
						//Error occured. 
					}
					else if(pid==0){
						//Execute the program, with args+2 being the pointer to the array of arguments.
						if(execvp(args[1],args+2)<0){
							printf("myshell: ERROR %s\n",strerror(errno));
						}
					}else{
						printf("myshell: process %d started.\n",pid);
					}

					break;
				case WAIT:
					break;
				case RUN:
					break;
				case KILL:
					break;
				case STOP:
					break;
				case CONT:
					break;
				case -1:
					//Error:
					break;


			}


		}
		
	}
	exit(0);
}
