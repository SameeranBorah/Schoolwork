/*
 * John F. Lake, Jr. 
 * CSE30341, Project 2
 * Myshell
 *
 */
//Debugging: 
//TODO: fix error messages
//TODO: Fix start command
//TODO: Implement kill, stop, and continue

//#define DEBUG 1


//Includes: 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
		printf("myshell: ERROR, Unknown command %s",command);
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
		if(strcmp(input,"\n")==0){
			return -1;
		}

		//Testing user input: 
		#ifdef DEBUG
			printf("You entered: %s",input);
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
						printf("Command: %s",args[argsNo]);
					#endif
					//Increment the number of arguments read: 
					argsNo++;
				}
			}else{
				if((args[argsNo] = strtok(NULL,"	 \n"))==NULL){
					break;
				}else{
					#ifdef DEBUG
						printf("Argument %d: %s",argsNo,args[argsNo]);
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
	pid_t pid;


	while(shellRunning){

	
		printf("\nmyshell>");
		int numArgs;
		int status;
		int s;
		if((numArgs = getInput(input,args))==-1){
			//Print error message
		}else{
			//Interpret/use the input: 
			switch(interpretCommand(args[0])){
				case EXIT:
					shellRunning  = 0;
					break;
				case START:;
					//Here, we will fork and call the execvp() function: 
					if(numArgs == 1){
						printf("myshell: ERROR, NEED TO PASS COMMAND IN!");
						break;
					}
					pid = fork();
				
					//If this is a child process, run: 
					if(pid<0){
						//Error occured. 
						//TODO: Make error message
					}
					else if(pid==0){
						//Execute the program, with args+2 being the pointer to the array of arguments.
						if(execvp(args[1],args+1)<0){
							printf("\nmyshell: ERROR %s",strerror(errno));
						}
					}else{
						printf("myshell: process %d started.",pid);
						
					}
					break;
				case WAIT:;
					if((pid = wait(&status))<0){
						 printf("myshell: no processes left.");
					}else{
						if(WIFSIGNALED(status)){	
							s = WTERMSIG(status);
							printf("myshell: process %d exited with signal %d: %s",pid,s,strsignal(s));
						}else if(WIFEXITED(status)){
							printf("myshell: process %d exited normally with return value 0",pid);
						}

					}

					break;
				case RUN:
					//Very similar to start:
					//Here, we will fork and call the execvp() function: 
					if(numArgs == 1){
						printf("myshell: ERROR, NEED TO PASS COMMAND IN!");
						break;
					}
					pid = fork();

					//If this is a child process, run: 
					if(pid<0){
						//Error occured. 
						//TODO: Make error message
					}
					else if(pid==0){
						//Execute the program, with args+2 being the pointer to the array of arguments.
						if(execvp(args[1],args+1)<0){
							printf("\nmyshell: ERROR %s",strerror(errno));
						}
					}else{
						pid = waitpid(pid,&status,0);
						if(WIFSIGNALED(status)){	
							s = WTERMSIG(status);
							printf("myshell: process %d exited abnormally with signal %d: %s",pid,s,strsignal(s));
						}else if(WIFEXITED(status)){
							printf("myshell: process %d exited normally with return value 0",pid);
						}
					}

					break;
					//Right here, we're going to issue SIGKILL, SIGSTOP, and SIGCONT signals to the processes
				case KILL:
					break;
				case STOP:
					break;
				case CONT:
					break;
				case -1:
					//TODO:Make error message
					break;


			}


		}
		
	}
	exit(0);
}
