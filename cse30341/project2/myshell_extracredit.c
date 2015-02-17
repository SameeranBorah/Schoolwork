/*
 * John F. Lake, Jr. 
 * CSE30341, Project 2
 * Myshell command prompt
 *
 */

//#define DEBUG 1


//Includes: 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

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
#define ARGER 1




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
		return -1;
}


/*
 *Simple function for making error messages cleaner: 
 *
 */
void error(int num,int argFlag){
	if(argFlag == ARGER){
		printf("myshell: error: wrong number of arguments!");
	}else
		printf("myshell: error: %s",strerror(num));
}

/*
 * getInput() returns the number of arguments read
 * @param input The input string from the user.
 * @param args The array of arguments from the user.
 * @param return int (Number of arguments when successful, -ARGER if a failure occurs)
 */
int getInput(char *input, char ** args){
	//Get user input: 
	if(fgets(input,BUF_LEN,stdin)!=NULL){
		//If they enter nothing, return 0.
		if(strcmp(input,"\n")==0){
			return 0;
		}
		int argsNo=0;
		while(argsNo<MAX_ARGS){
			//Strtok needs input of NULL after first token, so you need to process the first differently: 
			if(argsNo==0){
				if((args[argsNo] = strtok(input,"	 \n"))==NULL){
					return -1;
				}else{	
					argsNo++;
				}
			//After the first, call strtok with NULL:
			}else{
				if((args[argsNo] = strtok(NULL,"	 \n"))==NULL){
					break;
				}else{
					argsNo++;
				}
			}
		}
		return argsNo;
	}else{
		return -1;
	}
}

/*
 * Start
 * Starts a process and keeps track of it until a user calls wait
 */
void start(int numArgs, pid_t pid, char** args,int *numP){ 
//Here, we will fork and call the execvp() function:
	char** realArgs = malloc(4096);
	if(numArgs == 1) error(0,ARGER);
	else{
		//Fork and create a child process:
		if((pid = fork())<0) error(errno,0);
	
		//Child process:
		else if(pid==0){
			int hasIn = 0;
			int hasOut = 0;
			int hasBoth = 0;
			int fdIn;
			int fdOut;
			int n;
			int i = 0;
			for(n = 1;n<numArgs;n++){
				if(args[n][0] == '<'){
					//Need to make an infile: 
					if((fdIn = open(args[n]+1,O_RDONLY,0))!=-1){
						if(hasOut) hasBoth = 1;
						else hasIn=1;	
					}
				}else if (args[n][0]=='>'){
					int mode = 400;
					//Need to make an outfile:
					if((fdOut = creat(args[n]+1,mode))!=-1){
						if(hasIn) hasBoth = 1;
						else hasOut = 1;
					}
				}else{
					realArgs[i] = args[n];
					i++;
				}
			}
			if(hasBoth){
				dup2(fdOut,1);
				dup2(fdIn,0);
			}else if (hasIn){
				dup2(fdIn,0);
			}else if (hasOut){
				dup2(fdOut,1);
			}

			//Execute the program, with args+2 being the pointer to the array of arguments.
			if(execvp(args[1],realArgs)<0) error(errno,0);
		//Parent Process:
		}else{
			printf("myshell: process %d started.",pid);
			(*numP)++;
		}
	}
}

/*
 * Wait
 * Waits for a process to finish and prints the exit code
 */
void waitFor(int s, int status, pid_t pid,int* numP){
	if((pid = wait(&status))<0){
		error(errno,0);
	}else{
		if(WIFSIGNALED(status)){	
			s = WTERMSIG(status);
			printf("myshell: process %d exited with signal %d: %s",pid,s,strsignal(s));
		}else if(WIFEXITED(status)){
			printf("myshell: process %d exited normally with return value 0",pid);
		}
		(*numP)--;
	}
}

/*
 * Run
 * Like start, but immediately exits. 
 */
void run(int numArgs, int s,int status, pid_t pid, char** args){
	//Very similar to start:
	//Here, we will fork and call the execvp() function: 
	char** realArgs = malloc(4096);
	if(numArgs == 1) error(0,ARGER);
	else{

		//Fork/create child:
		if((pid = fork())<0) error(errno,0);

		//Child process:
		else if(pid==0){
			int hasIn = 0;
			int hasOut = 0;
			int hasBoth = 0;
			int fdIn;
			int fdOut;
			int n;
			int i = 0;
			for(n = 1;n<numArgs;n++){
				if(args[n][0] == '<'){
					//Need to make an infile: 
					if((fdIn = open(args[n]+1,O_RDONLY,0))!=-1){
						if(hasOut) hasBoth = 1;
						else hasIn=1;	
					}
				}else if (args[n][0]=='>'){
					int mode = 400;
					//Need to make an outfile:
					if((fdOut = creat(args[n]+1,mode))!=-1){
						if(hasIn) hasBoth = 1;
						else hasOut = 1;
					}
				}else{
					realArgs[i] = args[n];
					i++;
				}
			}
			if(hasBoth){
				dup2(fdOut,1);
				dup2(fdIn,0);
			}else if (hasIn){
				dup2(fdIn,0);
			}else if (hasOut){
				dup2(fdOut,1);
			}

			//Execute the program, with args+2 being the pointer to the array of arguments.
			if(execvp(args[1],realArgs)<0) error(errno,0);
		//Parent:
		}else{
			if((pid = waitpid(pid,&status,0))<0)error(errno,0);
			else{
				if(WIFSIGNALED(status)){	
					s = WTERMSIG(status);
					printf("myshell: process %d exited abnormally with signal %d: %s",pid,s,strsignal(s));
				}else if(WIFEXITED(status)){
					printf("myshell: process %d exited normally with return value 0",pid);
				}
			}
		}
	}
}


//Handles kill, stop, and continue
void killStopCont(int numArgs,int s, int status,int type, pid_t pid, char** args,int*numP){
	if(numArgs != 2){
		error(0,ARGER);
	}else{
		pid = atoi(args[1]);	
		switch(type){
			case KILL: 
				if(kill(pid,SIGKILL)<0) error(errno,0);
				else{
					if((pid = waitpid(pid,&status,0))<0) error(errno,0);
					else{
						if(WIFSIGNALED(status)){	
							s = WTERMSIG(status);
							printf("myshell: process %d exited abnormally with signal %d: %s",pid,s,strsignal(s));
						}else if(WIFEXITED(status)){
							printf("myshell: process %d exited normally with return value 0",pid);
						}
					}
				}
				break;
			case STOP: 
				if(kill(pid,SIGSTOP)<0) error(errno,0);
				else printf("myshell: process %d stopped",pid);
				break;
			case CONT:
				if(kill(pid,SIGCONT)<0) error(errno,0);
				else printf("myshell: process %d continued",pid);
				break;
		}
		(*numP)--;
	}
}


/*
 *The main function which runs the myshell program
 *If the user calls ./myshell [NAME], they can place their name in the promt (like a bash shell)
 */
int main(int argc, char ** argv){
	//Easter egg for making a more personalized shell: 
	int personal = 0;
	if(argc >1) personal = 1;


	//Argument buffer, input buffer, flag for keeping the program running, and the pid variable:
	char * args[MAX_ARGS];
	char input[BUF_LEN];
	int shellRunning = 1;
	pid_t pid;


	//Used to keep track of the processes currently running: 
	int numProcesses=0;
	

	while(shellRunning){

		//Allow the user to pass their name as an argument (simply cosmetic):
		if(personal)
			printf("\n[myshell-%s-]$",argv[1]);
		else
			printf("\nmyshell>");


		int numArgs;
		int status;
		int s;
		if((numArgs = getInput(input,args))==-1){
			shellRunning = 0;
			exit(0);
		}else if (numArgs == 0){

		}else {
			int command = interpretCommand(args[0]);
			//Interpret/use the input: 
			switch(command){
				case EXIT:
					shellRunning  = 0;
					break;
				case START:
					start(numArgs,pid,args,&numProcesses);
					break;
				case WAIT:
					waitFor(s,status,pid,&numProcesses);			
					break;
				case RUN:
					run(numArgs,s,status,pid,args);
					break;
				case KILL:
				case STOP:
				case CONT:
					//All of these only differ by a small amount, so there's one function: 
					killStopCont(numArgs,s,status,command,pid,args,&numProcesses);
					break;
				case -1:
					printf("myshell: command not recognized: %s",args[0]);
					break;
			}
		}
	}
	exit(0);
}
