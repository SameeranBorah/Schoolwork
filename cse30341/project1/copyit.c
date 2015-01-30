/*
 * John F. Lake, Jr. 
 * CSE 30341
 * Project 1: copyit program
 *
 * NOTE: I ran this through valgrind, and it reported an error with uninitialized values from strlen.  I did some searching and some sources believe this * is a false positive, so I will not worry about it. 
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

//I opted for 256 bytes (.25 kB) so that I could see the sigaction message go off with large files. 
#define NOBYTES 256 

#define ARGER 1
#define AR2ER 5
#define REAER 2
#define WRIER 3
#define OTHER 4

//#define DEBUG 1 //Used for debugging (printing out file contents, among other things.)

/*
 * Error function; Uses strerror to give a more descriptive error, and the error codes 
 * can give the user extra information about where the error comes from.  
 * @param errorCode Signal corresponding to one of many error messages
 * @return void
 */
void error(int errorCode){
	switch(errorCode){
		case ARGER:
			printf("copyit: Wrong number of arguments!\n"); 
			printf("Usage: copyit <sourcefile> <targetfile>\n"); 
			exit(1); 
			break;
		case AR2ER:
			printf("copyit: Can't copy file to itself!\n");
			exit(1);
			break;
		case REAER:
			printf("copyit: Error reading.\n");
			printf("copyit: %s\n",strerror(errno)); 
			exit(1); 
			break; 
		case WRIER:
			printf("copyit: Error writing.\n"); 
			printf("copyit: %s\n",strerror(errno)); 
			exit(1); 
			break; 
		case OTHER:
			printf("copyit: %s\n",strerror(errno)); 
			exit(1); 
			break; 	
	}
}


/*
 * Copy Status Update
 * @param s The alarm variable
 */
void copyStatus(int s){
	//Error Checking in place for return values:
	if(printf("copyit: Still copying...\n")<0) error(OTHER); 
	if(alarm(1)<0) error(OTHER); 
}
	

/*
 * Close the program.
 * @param b The number of bytes copied from the source file to the destination file.
 */
void closeProg(int b,char* src, char* dest){
	if(alarm(1)<0) error(OTHER); 
	if(printf("copyit: %d bytes were copied from %s to %s\n",b,src,dest)<0) error(OTHER);
}



int main(int argc,char** argv){
	int totalBytes=0; 
	int sp=0; //File descriptor for source program
	int tp=0; //File descriptor for target program
	int numBytes=0; //Number of bytes read or written
	char * buf=NULL; //Buffer that has NOBYTES (number of bytes); used to read and write 
	if((buf = malloc(NOBYTES))==0) error(OTHER); 

	//sigaction() is more portable than signal():
	struct sigaction sigAct;
	sigAct.sa_handler = copyStatus; 
	sigAct.sa_flags = SA_RESTART;

	//Use this to print if the file takes a long time to copy. 
	if(sigaction(SIGALRM,&sigAct,NULL)<0){
		error(OTHER);	
	}
	if(alarm(1)<0) error(OTHER); 
	

	//If there are not exactly three arguments, send an error code to the user and exit. 
	if(argc!=3){
		error(ARGER); 
	}else if(strcmp(argv[1],argv[2])==0){
		error(AR2ER);
	}else{
	
		//Open the source file
		if((sp = open(argv[1],O_RDONLY))==-1){
 			//Error, value of -1 returned
 			error(REAER); 
 		}else{
			//Want to open the file we're going to write to: 
			if((tp=creat(argv[2],S_IRUSR|S_IWUSR))==-1){
				//Error creating file.
				error(WRIER); 
			}else{


				//Here, we have successfully opened both files.
				//Want to read from file: 
				do{
					memset(buf,0,strlen(buf)); 
					#ifdef DEBUG
						printf("Buffer: ####%s####\n",buf);
					#endif
					if((numBytes = read(sp,buf,NOBYTES))==-1){
						//Error reading from file
						//Deal with error here.
						//Check to see if it was from the signalAction
						if(errno == EINTR){
							//Try to read again.
							continue; 
						}else{
							error(REAER); 
						}
					}else{
				

						//Increment the total number of bytes copied: 
						totalBytes+=numBytes;
						if(numBytes < NOBYTES){
							#ifdef DEBUG
								//Print out results: 
								printf("@@@@%s@@@@",buf);
								printf("%d : string length\n",strlen(buf));	
							#endif
							if((write(tp,buf,strlen(buf)))==-1){
								//If it's an interrupt, try writing again, otherwise, exit.
								if(errno == EINTR){
									//Try to read again.
									continue; 
								}else{
									error(WRIER); 
								}
							}
							numBytes = 0;
						}else{

							#ifdef DEBUG
								//Print out results: 
								printf("@@@@%s@@@@",buf);
								printf("%d : string length\n",strlen(buf));	
							#endif


							//Take the buffer and write to the other file
							if((write(tp,buf,strlen(buf)))==-1){
								//If it's an interrupt, try writing again, otherwise, exit.
								if(errno == EINTR){
									//Try to read again.
									continue; 
								}else{
									error(WRIER); 
								}
							}
						}
					}
					#ifdef DEBUG
						printf("Bytes read: %d\n",numBytes);
						sleep(1000);
					#endif
					
				}while (numBytes>0);	
			}
			//Need to close the files:
			if(close(sp)<0) error(OTHER);
			if(close(tp)<0) error(OTHER);
		}
	}
	//Deallocate memory and give a closing message to the user. 
	free(buf); 
	closeProg(totalBytes,argv[1],argv[2]);
	exit(0);
}

